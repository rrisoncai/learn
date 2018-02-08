#include <cmath>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include "ceres/ceres.h"
#include "ceres/rotation.h"
// Read a Bundle Adjustment in the Large dataset.
class BALProblem {
public:
    ~BALProblem() {
        delete[] point_index_;
        delete[] camera_index_;
        delete[] observations_;
        delete[] parameters_;
    }

    int num_observations()       const { return num_observations_;               }
    const double* observations() const { return observations_;                   }
    double* mutable_cameras()          { return parameters_;                     }
    double* mutable_points()           { return parameters_  + 9 * num_cameras_; }
    double* mutable_camera_for_observation(int i) {
        return mutable_cameras() + camera_index_[i] * 9;
    }

    double* mutable_point_for_observation(int i) {
        return mutable_points() + point_index_[i] * 3;
    }

    bool LoadFile(const char* filename) {
        FILE* fptr = fopen(filename, "r");
        if (fptr == NULL) {
            return false;
        };

        FscanfOrDie(fptr, "%d", &num_cameras_);
        FscanfOrDie(fptr, "%d", &num_points_);
        FscanfOrDie(fptr, "%d", &num_observations_);
        point_index_ = new int[num_observations_];
        camera_index_ = new int[num_observations_];
        observations_ = new double[2 * num_observations_];
        num_parameters_ = 9 * num_cameras_ + 3 * num_points_;
        parameters_ = new double[num_parameters_];
        for (int i = 0; i < num_observations_; ++i) {
            FscanfOrDie(fptr, "%d", camera_index_ + i);
            FscanfOrDie(fptr, "%d", point_index_ + i);
            for (int j = 0; j < 2; ++j) {
                FscanfOrDie(fptr, "%lf", observations_ + 2*i + j);
            }
        }
        for (int i = 0; i < num_parameters_; ++i) {
            FscanfOrDie(fptr, "%lf", parameters_ + i);
        }

        return true;
    }
    void WriteFile(const std::string& filename) {
        std::ofstream of(filename.c_str());

        of<< "ply"
          << '\n' << "format ascii 1.0"
          << '\n' << "element vertex " << num_cameras_ + num_points_
          << '\n' << "property float x"
          << '\n' << "property float y"
          << '\n' << "property float z"
          << '\n' << "property uchar red"
          << '\n' << "property uchar green"
          << '\n' << "property uchar blue"
          << '\n' << "end_header" << std::endl;

        // Export extrinsic data (i.e. camera centers) as green points.
        double angle_axis[3];
        double center[3];
        for(int i = 0; i < num_cameras_; ++i){
            const double* camera = mutable_cameras() + 9 * i;
            ceres::AngleAxisRotatePoint(camera, angle_axis, center);
            of << center[0] << ' ' << center[1] << ' ' << center[2]
               << "0 255 0" << '\n';
        }

        // Export the structure (i.e. 3D Points) as white points.
        const double* points = parameters_ + 9 * num_cameras_;
        for(int i = 0; i < num_points_; ++i){
            const double* point = points + i * 3;
            for(int j = 0; j < 3; ++j){
                of << point[j] << ' ';
            }
            of << "255 255 255\n";
        }
        of.close();
    }

private:
    template<typename T>
    void FscanfOrDie(FILE *fptr, const char *format, T *value) {
        int num_scanned = fscanf(fptr, format, value);
        if (num_scanned != 1) {
            LOG(FATAL) << "Invalid UW data file.";
        }
    }
    int num_cameras_;
    int num_points_;
    int num_observations_;
    int num_parameters_;
    int* point_index_;
    int* camera_index_;
    double* observations_;
    double* parameters_;
};

struct ReprojectionError {
    ReprojectionError(double observed_x, double observed_y)
            : observed_x(observed_x), observed_y(observed_y) {}
    template <typename T>
    bool operator()(const T* const camera,
                    const T* const point,
                    T* residuals) const {

        T p[3];
        // rotation
        ceres::AngleAxisRotatePoint(camera, point, p);
        // translation
        p[0] += camera[3];
        p[1] += camera[4];
        p[2] += camera[5];
        T xp = - p[0] / p[2]; // -X/Z
        T yp = - p[1] / p[2]; // -Y/Z

        // distortion
        const T& l1 = camera[7];
        const T& l2 = camera[8];
        T r2 = xp*xp + yp*yp;
        T distortion = 1.0 + r2  * (l1 + l2  * r2);
        const T& focal = camera[6];

        T predicted_x = focal * distortion * xp;
        T predicted_y = focal * distortion * yp;

        residuals[0] = predicted_x - observed_x;
        residuals[1] = predicted_y - observed_y;
        return true;
    }

    static ceres::CostFunction* Create(const double observed_x,
                                       const double observed_y) {
        return (new ceres::AutoDiffCostFunction<ReprojectionError, 2, 9, 3>(
                new ReprojectionError(observed_x, observed_y)));
    }

    double observed_x;
    double observed_y;
};
int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);

    if (argc != 2) {
        std::cerr << "usage: simple_bundle_adjuster <bal_problem>\n";
        return 1;
    }

    BALProblem bal_problem;
    if (!bal_problem.LoadFile(argv[1])) {
        std::cerr << "ERROR: unable to open file " << argv[1] << "\n";
        return 1;
    }

    // write to init.ply
    bal_problem.WriteFile("init.ply");

    const double* observations = bal_problem.observations();
    ceres::Problem problem;
    for (int i = 0; i < bal_problem.num_observations(); ++i) {
        ceres::CostFunction* cost_function = ReprojectionError::Create(observations[2 * i + 0],
                                                                       observations[2 * i + 1]);
        problem.AddResidualBlock(cost_function,
                                 NULL /* squared loss */,
                                 bal_problem.mutable_camera_for_observation(i),
                                 bal_problem.mutable_point_for_observation(i));
    }

    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_SCHUR;
    options.minimizer_progress_to_stdout = true;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);
    std::cout << summary.FullReport() << "\n";

    // write to final.ply
    bal_problem.WriteFile("final.ply");

    return 0;
}