#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace std;

Eigen::Matrix3d antisym(Eigen::Vector3d w) {
    Eigen::Matrix3d ret;
    ret << 0, -w[2], w[1], w[2], 0, -w[0], -w[1], w[0], 0;
    return ret;
}
int main()
{
    // initial rotation matrix is identity
    Eigen::Matrix3d r0 = Eigen::Matrix3d::Identity();
    Eigen::Quaterniond q0(r0);

    // rotation vector, (0.01, 0.02, 0.03)
    Eigen::Vector3d w(0.01, 0.02, 0.03);
    Eigen::Quaterniond q1(1.0, 0.01/2, 0.02/2, 0.03/2);

    // second order exponential mapping
    Eigen::Matrix3d asym = antisym(w);
    Eigen::Matrix3d r1 = Eigen::Matrix3d::Identity() + asym + 0.5 * asym * asym;

    cout << "Before rotation q0:" << endl << q0.toRotationMatrix() << endl << endl;
    cout << "Before rotation r0:" << endl << r0 << endl << endl;

    r0 = r0 * r1;
    q0 = q0 * q1;
    q0.normalize();

    cout << "After rotation q0:" << endl << q0.toRotationMatrix() << endl << endl;
    cout << "After rotation r0:" << endl << r0 << endl << endl;

    return 0;
}