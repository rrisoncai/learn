#include <sophus/se3.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/SVD>
#include <string>
#include <iostream>
#include <fstream>

// need pangolin for plotting trajectory
#include <pangolin/pangolin.h>

using namespace std;

typedef vector<Sophus::SE3, Eigen::aligned_allocator<Sophus::SE3>> trace;
// path to trajectory file
string input_file = "./compare.txt";

// function for plotting trajectory, don't edit this code
// start point is red and end point is blue
void DrawTrajectory(trace, trace);
void pose_estimation_3d3d (
    const vector<Eigen::Vector3d>& pts1,
    const vector<Eigen::Vector3d>& pts2,
    Eigen::Matrix3d& R, Eigen::Vector3d& t
);

int main(int argc, char **argv) {

    trace pose_g, pose_e;
    vector<Eigen::Vector3d> trace_g, trace_e;

    ifstream fin(input_file);

    Eigen::Quaterniond qg, qe;
    Eigen::Vector3d tg, te;
    double ts;

    while(fin
        >> ts >> te[0] >> te[1] >> te[2]
        >> qe.x() >> qe.y() >> qe.z() >> qe.w()
        >> ts >> tg[0] >> tg[1] >> tg[2]
        >> qg.x() >> qg.y() >> qg.z() >> qg.w())
    {
        Sophus::SE3 g(qg, tg);
        Sophus::SE3 e(qe, te);
        pose_g.push_back(g);
        pose_e.push_back(e);
        trace_g.push_back(tg);
        trace_e.push_back(te);
    }

    fin.close();

    Eigen::Matrix3d R;
    Eigen::Vector3d t;
    pose_estimation_3d3d(trace_e, trace_g, R, t);
    cout << "R:" << endl;
    cout << R << endl;
    cout << "t:" << endl;
    cout << t << endl;
    Sophus::SE3 SE3_Rt(R, t);

    for(int i = 0; i !=pose_g.size(); ++i)
    {
        pose_g[i] = SE3_Rt * pose_g[i];
    }

    // draw trajectory in pangolin
    DrawTrajectory(pose_g, pose_e);
    return 0;
}

/*******************************************************************************************/
void DrawTrajectory(trace pose1, trace pose2) {
    if (pose1.empty() || pose2.empty()) {
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
        for (size_t i = 0; i < pose1.size() - 1; i++) {
            glColor3f(1.0f, 0.0f, 0.0f);
            glBegin(GL_LINES);
            auto p1 = pose1[i], p2 = pose1[i + 1];
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
            glEnd();
        }
        for (size_t i = 0; i < pose2.size() - 1; i++) {
            glColor3f(0.0f, 0.0f, 1.0f);
            glBegin(GL_LINES);
            auto p1 = pose2[i], p2 = pose2[i + 1];
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
            glEnd();
        }
        pangolin::FinishFrame();
        usleep(5000);   // sleep 5 ms
    }
}
void pose_estimation_3d3d (
    const vector<Eigen::Vector3d>& pts1,
    const vector<Eigen::Vector3d>& pts2,
    Eigen::Matrix3d& R, Eigen::Vector3d& t
)
{
    Eigen::Vector3d p1, p2;     // center of mass
    int N = pts1.size();
    for ( int i=0; i<N; i++ )
    {
        p1 += pts1[i];
        p2 += pts2[i];
    }
    p1 = p1 / N;
    p2 = p2 / N;
    vector<Eigen::Vector3d>     q1 ( N ), q2 ( N ); // remove the center
    for ( int i=0; i<N; i++ )
    {
        q1[i] = pts1[i] - p1;
        q2[i] = pts2[i] - p2;
    }

    // compute q1*q2^T
    Eigen::Matrix3d W = Eigen::Matrix3d::Zero();
    for ( int i=0; i<N; i++ )
    {
        W += q1[i] * q2[i].transpose();
    }

    // SVD on W
    Eigen::JacobiSVD<Eigen::Matrix3d> svd ( W, Eigen::ComputeFullU|Eigen::ComputeFullV );
    Eigen::Matrix3d U = svd.matrixU();
    Eigen::Matrix3d V = svd.matrixV();
    cout<<"U="<<U<<endl;
    cout<<"V="<<V<<endl;

    R = U* ( V.transpose() );
    t = p1 - R * p2;
}
