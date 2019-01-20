#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <string>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <sophus/se3.hpp>
#include <boost/format.hpp>
#include <pangolin/pangolin.h>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;
using namespace Eigen;

// this program shows how to use optical flow

string left_file = "./left.png";  // first image
string right_file = "./right.png";  // second image
string disparity_file = "./disparity.png";
boost::format fmtl("/Users/sheldon/ws/learn/shenlan_slam/final/dataset/00/image_0/%06d.png");
boost::format fmtr("/Users/sheldon/ws/learn/shenlan_slam/final/dataset/00/image_1/%06d.png");

//#define DRAW
typedef vector<Eigen::Vector3d, Eigen::aligned_allocator<Eigen::Vector3d>> VecVector3d;
typedef vector<Eigen::Vector2d, Eigen::aligned_allocator<Eigen::Vector2d>> VecVector2d;
typedef Eigen::Matrix<double, 6, 1> Vector6d;
typedef vector<Sophus::SE3d, Eigen::aligned_allocator<Sophus::SE3d>> trajectory;
// Camera intrinsics
// 内参
double fx = 718.856, fy = 718.856, cx = 607.1928, cy = 185.2157;
// 基线
double baseline = 0.573;

 Sophus::SE3d PNP(VecVector3d& p3d, VecVector2d& p2d, Matrix3d& K) {

     int iterations = 100;
     double cost = 0, lastCost = 0;
     int nPoints = p3d.size();
     cout << "points: " << nPoints << endl;

     Sophus::SE3d T_esti; // estimated pose

     for (int iter = 0; iter < iterations; iter++) {

         Matrix<double, 6, 6> H = Matrix<double, 6, 6>::Zero();
         Vector6d b = Vector6d::Zero();

         cost = 0;
         // compute cost
         for (int i = 0; i < nPoints; i++) {
             // compute cost for p3d[I] and p2d[I]
             // START YOUR CODE HERE
             Vector2d err;
             Vector4d p4d(p3d[i](0), p3d[i](1), p3d[i](2), 1);
             Vector4d TP4d = Sophus::SE3d::exp(T_esti.log()).matrix() * p4d;
             Vector3d TP3d(TP4d(0), TP4d(1), TP4d(2));
             Vector3d KTP3d = K * TP3d;
             Vector2d KTP2d(KTP3d(0) / KTP3d(2), KTP3d(1) / KTP3d(2));
             Vector2d error = p2d[i] - KTP2d;


             cost += error.norm();
 	    // END YOUR CODE HERE

 	    // compute jacobian
             Matrix<double, 2, 6> J;
             double x = p3d[i][0];
             double y = p3d[i][1];
             double z = p3d[i][2];
             J(0,0) = -fx / z;
             J(0,1) = 0;
             J(0,2) = fx * x / z / z;
             J(0,3) = fx * x * y / z / z;
             J(0,4) = -fx - fx * x * x / z / z;
             J(0,5) = fx * y / z;
             J(1,0) = 0;
             J(1,1) = -fy / z;
             J(1,2) = fy * y / z / z;
             J(1,3) = fy + fy * y * y / z / z;
             J(1,4) = -fy * x * y / z / z;
             J(1,5) = -fy * x / z;
             // START YOUR CODE HERE

             Vector2d e;
             e = error;
 	    // END YOUR CODE HERE

             H += J.transpose() * J;
             b += -J.transpose() * e;
         }

 	// solve dx
         Vector6d dx;

         // START YOUR CODE HERE

         dx = H.inverse() * b;
         // END YOUR CODE HERE

         if (isnan(dx[0])) {
             cout << "result is nan!" << endl;
             break;
         }

         if (iter > 0 && cost >= lastCost) {
             // cost increase, update is not good
             cout << "cost: " << cost << ", last cost: " << lastCost << endl;
             break;
         }

         // update your estimation
         // START YOUR CODE HERE

         T_esti = T_esti * Sophus::SE3d::exp(dx);
         // END YOUR CODE HERE

         lastCost = cost;

         cout << "iteration " << iter << " cost=" << cout.precision(12) << cost << endl;
     }

     cout << "estimated pose: \n" << T_esti.matrix() << endl;
     return T_esti;
 }

void OpticalFlowSingleLevel(
        const Mat &img1,
        const Mat &img2,
        const vector<KeyPoint> &kp1,
        vector<KeyPoint> &kp2,
        vector<bool> &success,
        bool inverse = false
);

// TODO implement this funciton
/**
 * multi level optical flow, scale of pyramid is set to 2 by default
 * the image pyramid will be create inside the function
 * @param [in] img1 the first pyramid
 * @param [in] img2 the second pyramid
 * @param [in] kp1 keypoints in img1
 * @param [out] kp2 keypoints in img2
 * @param [out] success true if a keypoint is tracked successfully
 * @param [in] inverse set true to enable inverse formulation
 */
void OpticalFlowMultiLevel(
        const Mat &img1,
        const Mat &img2,
        const vector<KeyPoint> &kp1,
        vector<KeyPoint> &kp2,
        vector<bool> &success,
        bool inverse = false
);

/**
 * get a gray scale value from reference image (bi-linear interpolated)
 * @param img
 * @param x
 * @param y
 * @return
 */
inline float GetPixelValue(const cv::Mat &img, float x, float y) {
    uchar *data = &img.data[int(y) * img.step + int(x)];
    float xx = x - floor(x);
    float yy = y - floor(y);
    return float(
            (1 - xx) * (1 - yy) * data[0] +
            xx * (1 - yy) * data[1] +
            (1 - xx) * yy * data[img.step] +
            xx * yy * data[img.step + 1]
    );
}


int main(int argc, char **argv) {

    ofstream fout("result.txt");
    trajectory poses;
    Sophus::SE3d I, ref;
    poses.push_back(I);
    ref = I;
    for(int i = 0; i < 1000; ++i) {
        // images, note they are CV_8UC1, not CV_8UC3
        cout << (fmtl%i).str() << endl;
        Mat img1 = imread((fmtl%i).str(), 0);
        Mat img2 = imread((fmtr%i).str(), 0);
        Mat img3 = imread((fmtl%(i+1)).str(), 0);

        // key points, using GFTT here.
        vector<KeyPoint> kp1;
        Ptr<GFTTDetector> detector = GFTTDetector::create(500, 0.01, 10); // maximum 500 keypoints
        //Ptr<SURF> detector = SURF::create(500); // maximum 500 keypoints
        detector->detect(img1, kp1);

        // then test multi-level LK
        vector<KeyPoint> kp2_multi;
        vector<bool> success_multi;
        OpticalFlowMultiLevel(img1, img2, kp1, kp2_multi, success_multi, true);

        vector<KeyPoint> kp3;
        vector<bool> kp3_good;
        OpticalFlowMultiLevel(img1, img3, kp1, kp3, kp3_good, true);
        VecVector3d p3d;
        VecVector2d p2d;
        Matrix3d K;
        K << fx, 0, cx, 0, fy, cy, 0, 0, 1;

        for (int k = 0; k < kp3.size(); k++) {
            if (success_multi[k] && kp3_good[k]) {
                double pixel_diff = (kp1[k].pt.x - kp2_multi[k].pt.x);
                if(pixel_diff != 0.0 && fx*baseline/pixel_diff && abs(kp1[k].pt.y - kp2_multi[k].pt.y) < 4) {
                    Vector3d uv(kp1[k].pt.x,kp1[k].pt.y,1);
                    double z = fx * baseline / pixel_diff;
                    Vector3d P = K.inverse() * z * uv;
                    p3d.push_back(P);
                    p2d.push_back(Vector2d(kp3[k].pt.x,kp3[k].pt.y));
                }
                else {
                    success_multi[k] = false;
                    kp3_good[k] = false;
                }
            }
        }

        Sophus::SE3d pose = PNP(p3d, p2d, K);
        pose = pose * ref;
        poses.push_back(pose);
        ref = pose;
        cout << "translation:" << endl << pose.matrix() << endl;
        fout << pose.translation().transpose() << endl;

        // plot the differences of those functions
        Mat img1_multi;
        cv::cvtColor(img1, img1_multi, CV_GRAY2BGR);
        Mat img2_multi;
        cv::cvtColor(img2, img2_multi, CV_GRAY2BGR);
        Mat img3_multi;
        cv::cvtColor(img3, img3_multi, CV_GRAY2BGR);

        #ifdef DRAW
        for (int i = 0; i < kp2_multi.size(); i++) {
            if (success_multi[i]) {
                cv::circle(img2_multi, kp2_multi[i].pt, 2, cv::Scalar(0, 250, 0), 2);
                cv::line(img2_multi, kp1[i].pt, kp2_multi[i].pt, cv::Scalar(0, 250, 0));
            }
            if (kp3_good[i]) {
                cv::circle(img3_multi, kp3[i].pt, 2, cv::Scalar(0, 250, 0), 2);
                cv::circle(img1_multi, kp1[i].pt, 2, cv::Scalar(0, 250, 0), 2);
                cv::line(img1_multi, kp1[i].pt, kp3[i].pt, cv::Scalar(0, 250, 0));
            }
        }

        cv::imshow("1 tracked multi level", img1_multi);
        cv::imshow("2 tracked multi level", img2_multi);
        cv::imshow("3 tracked multi level", img3_multi);
        cv::waitKey(0);
        #endif
    }
    return 0;
}

void OpticalFlowSingleLevel(
        const Mat &img1,
        const Mat &img2,
        const vector<KeyPoint> &kp1,
        vector<KeyPoint> &kp2,
        vector<bool> &success,
        bool inverse
) {

    // parameters
    int half_patch_size = 8;
    int iterations = 100;
    bool have_initial = !kp2.empty();

    for (size_t i = 0; i < kp1.size(); i++) {
        auto kp = kp1[i];
        double dx = 0, dy = 0; // dx,dy need to be estimated
        if (have_initial) {
            dx = kp2[i].pt.x - kp.pt.x;
            dy = kp2[i].pt.y - kp.pt.y;
        }

        double cost = 0, lastCost = 0;
        bool succ = true; // indicate if this point succeeded

        // Gauss-Newton iterations
        for (int iter = 0; iter < iterations; iter++) {
            Eigen::Matrix2d H = Eigen::Matrix2d::Zero();
            Eigen::Vector2d b = Eigen::Vector2d::Zero();
            cost = 0;

            if (kp.pt.x + dx <= half_patch_size || kp.pt.x + dx >= img1.cols - half_patch_size ||
                kp.pt.y + dy <= half_patch_size || kp.pt.y + dy >= img1.rows - half_patch_size) {   // go outside
                succ = false;
                break;
            }

            // compute cost and jacobian
            for (int x = -half_patch_size; x < half_patch_size; x++)
                for (int y = -half_patch_size; y < half_patch_size; y++) {

                    // TODO START YOUR CODE HERE (~8 lines)
                    float x1 = kp.pt.x + x;
                    float y1 = kp.pt.y + y;
                    double error = (GetPixelValue(img1,x1,y1)-GetPixelValue(img2,x1+dx,y1+dy));
                    Eigen::Vector2d J;  // Jacobian
                    if (inverse == false) {
                        // Forward Jacobian
                        J[0] = (GetPixelValue(img2,x1+dx+1,y1+dy) - GetPixelValue(img2,x1+dx-1,y1+dy))/2;
                        J[1] = (GetPixelValue(img2,x1+dx,y1+dy+1) - GetPixelValue(img2,x1+dx,y1+dy-1))/2;
                    } else {
                        // Inverse Jacobian
                        // NOTE this J does not change when dx, dy is updated, so we can store it and only compute error
                        J[0] = (GetPixelValue(img1,x1+1,y1) - GetPixelValue(img1,x1-1,y1))/2;
                        J[1] = (GetPixelValue(img1,x1,y1+1) - GetPixelValue(img1,x1,y1-1))/2;
                    }

                    // compute H, b and set cost;
                    H += J * J.transpose();
                    b += J.transpose() * error;
                    cost += error * error;
                    // TODO END YOUR CODE HERE
                }

            // compute update
            // TODO START YOUR CODE HERE (~1 lines)
            Eigen::Vector2d update = H.inverse() * b;
            // TODO END YOUR CODE HERE

            if (isnan(update[0])) {
                // sometimes occurred when we have a black or white patch and H is irreversible
                cout << "update is nan" << endl;
                succ = false;
                break;
            }
            if (iter > 0 && cost > lastCost) {
                cout << "cost increased: " << cost << ", " << lastCost << endl;
                break;
            }

            // update dx, dy
            dx += update[0];
            dy += update[1];
            //dy += 0;
            lastCost = cost;
            succ = true;
        }

        success.push_back(succ);

        // set kp2
        if (have_initial) {
            kp2[i].pt = kp.pt + Point2f(dx, dy);
        } else {
            KeyPoint tracked = kp;
            tracked.pt += cv::Point2f(dx, dy);
            kp2.push_back(tracked);
        }
    }
}

void OpticalFlowMultiLevel(
        const Mat &img1,
        const Mat &img2,
        const vector<KeyPoint> &kp1,
        vector<KeyPoint> &kp2,
        vector<bool> &success,
        bool inverse) {

    // parameters
    int pyramids = 5;
    double pyramid_scale = 0.5;
    double scales[] = {1.0, 0.5, 0.25, 0.125, 0.0625};

    // create pyramids
    vector<Mat> pyr1, pyr2; // image pyramids
    // TODO START YOUR CODE HERE (~8 lines)
    for (int i = 0; i < pyramids; i++) {
        Mat dst1;
        Mat dst2;
        resize(img1, dst1, Size(), scales[i], scales[i]);
        resize(img2, dst2, Size(), scales[i], scales[i]);
        pyr1.push_back(dst1.clone());
        pyr2.push_back(dst2.clone());
    }

    vector<KeyPoint> kp2_scale;
    for(int i = pyramids - 1; i >= 0; --i)
    {
        vector<KeyPoint> kp1_scale = kp1;
        for(int j = 0; j != kp1_scale.size(); ++j)
        {
            kp1_scale[j].pt.x *= scales[i];
            kp1_scale[j].pt.y *= scales[i];
        }

        for(int j = 0; j != kp2_scale.size(); ++j)
        {
            kp2_scale[j].pt.x *= scales[i];
            kp2_scale[j].pt.y *= scales[i];
        }

        OpticalFlowSingleLevel(pyr1[i], pyr2[i], kp1_scale, kp2_scale, success, inverse);

        for(int j = 0; j != kp2_scale.size(); ++j)
        {
            kp2_scale[j].pt.x /= scales[i];
            kp2_scale[j].pt.y /= scales[i];
        }
    }

    kp2 = kp2_scale;
}
