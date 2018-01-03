//
// Created by 高翔 on 2017/12/19.
// 本程序演示如何从Essential矩阵计算R,t
//

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace Eigen;

#include <sophus/so3.h>

#include <iostream>

using namespace std;

int main(int argc, char **argv) {

    // 给定Essential矩阵
    Matrix3d E;
    E << -0.0203618550523477, -0.4007110038118445, -0.03324074249824097,
            0.3939270778216369, -0.03506401846698079, 0.5857110303721015,
            -0.006788487241438284, -0.5815434272915686, -0.01438258684486258;

    // 待计算的R,t
    Matrix3d R;
    Vector3d t;

    // SVD and fix sigular values
    // START YOUR CODE HERE
    Matrix3d R_zp, R_zn, sigma;
    MatrixXd U, V;
    Vector3d singular;
    R_zn << 0, 1, 0, 1, 0, 0, 0, 0, 1;
    R_zp << 0, 1, 0, -1, 0, 0, 0, 0, 1;
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(E, Eigen::ComputeFullV | Eigen::ComputeFullU);
    singular = svd.singularValues();
    double diag = (singular(0) + singular(1)) / 2;
    sigma << diag, 0, 0, 0, diag, 0, 0, 0, 0;
    U = svd.matrixU();
    V = svd.matrixV();


    // END YOUR CODE HERE

    // set t1, t2, R1, R2
    // START YOUR CODE HERE
    Matrix3d t_wedge1;
    Matrix3d t_wedge2;
    t_wedge1 = U * R_zp * sigma * U.transpose();
    t_wedge2 = U * R_zn * sigma * U.transpose();

    Matrix3d R1;
    Matrix3d R2;
    R1 = U * R_zp.transpose() * V.transpose();
    R2 = U * R_zn.transpose() * V.transpose();
    // END YOUR CODE HERE

    cout << "R1 = " << R1 << endl;
    cout << "R2 = " << R2 << endl;
    cout << "t1 = " << Sophus::SO3::vee(t_wedge1) << endl;
    cout << "t2 = " << Sophus::SO3::vee(t_wedge2) << endl;

    // check t^R=E up to scale
    Matrix3d tR = t_wedge1 * R1;
    cout << "t^R = " << tR << endl;
    cout << "E-t^R = " << E-tR << endl;

    return 0;
}
