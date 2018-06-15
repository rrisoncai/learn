#include <sophus/se3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>

// need pangolin for plotting trajectory
#include <pangolin/pangolin.h>

using namespace std;

// path to trajectory file
string trajectory_file = "./trajectory.txt";
string groundtruth_file = "./groundtruth.txt";
string estimateion_file = "./estimated.txt";

// function for plotting trajectory, don't edit this code
// start point is red and end point is blue
void DrawTrajectory(vector<Sophus::SE3, Eigen::aligned_allocator<Sophus::SE3>>);
double CalcRMSE(string groundtruth, string estimation);

int main(int argc, char **argv) {

    vector<Sophus::SE3, Eigen::aligned_allocator<Sophus::SE3>> poses;
    CalcRMSE(groundtruth_file, estimateion_file);

    /// implement pose reading code
    // start your code here (5~10 lines)
    ifstream fin(trajectory_file);

    Eigen::Quaterniond q;
    Eigen::Vector3d t;
    double ts;

    while(fin >> ts >> t[0] >> t[1] >> t[2] >> q.x() >> q.y() >> q.z() >> q.w())
    {
        Sophus::SE3 se3_qt(q, t);
        poses.push_back(se3_qt);
    }

    fin.close();

    // end your code here

    // draw trajectory in pangolin
    DrawTrajectory(poses);
    return 0;
}

/*******************************************************************************************/
void DrawTrajectory(vector<Sophus::SE3, Eigen::aligned_allocator<Sophus::SE3>> poses) {
    if (poses.empty()) {
        cerr << "Trajectory is empty!" << endl;
        return;
    }

    // create pangolin window and plot the trajectory
    pangolin::CreateWindowAndBind("Trajectory Viewer", 1024, 768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
            pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
    );

    pangolin::View &d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1.0, -1024.0f / 768.0f)
            .SetHandler(new pangolin::Handler3D(s_cam));


    while (pangolin::ShouldQuit() == false) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        d_cam.Activate(s_cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glLineWidth(2);
        for (size_t i = 0; i < poses.size() - 1; i++) {
            glColor3f(1 - (float) i / poses.size(), 0.0f, (float) i / poses.size());
            glBegin(GL_LINES);
            auto p1 = poses[i], p2 = poses[i + 1];
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
            glEnd();
        }
        pangolin::FinishFrame();
        usleep(5000);   // sleep 5 ms
    }

}

double CalcRMSE(string groundtruth, string estimation)
{
    ifstream gtr_cin(groundtruth);
    ifstream est_cin(estimation);
    Eigen::Quaterniond qt, qe;
    Eigen::Vector3d tt, te;
    double timestamp;
    double err = 0;
    vector<double> v_err;
    int length = 0;

    while(
        gtr_cin >> timestamp >> tt[0] >> tt[1] >> tt[2] >> qt.x() >> qt.y() >> qt.z() >> qt.w() &&
        est_cin >> timestamp >> te[0] >> te[1] >> te[2] >> qe.x() >> qe.y() >> qe.z() >> qe.w()
    )
    {
        Sophus::SE3 gtr(qt,tt);
        Sophus::SE3 est(qe,te);
        Sophus::SE3 tmp;

        Eigen::Matrix<double,6,1> err_i = (gtr.inverse() * est).log();

        err += err_i.norm() * err_i.norm();
        length++;
    }

    gtr_cin.close();
    est_cin.close();

    err /= length;
    err = sqrt(err);
    cout << "RMSE between groundtruth and estimation: " << err << endl;
    return err;

}
