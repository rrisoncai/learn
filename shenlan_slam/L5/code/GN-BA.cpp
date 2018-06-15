//
// Created by xiang on 12/21/17.
//

#include <Eigen/Core>
#include <Eigen/Dense>

using namespace Eigen;

#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "sophus/se3.h"

using namespace std;

typedef vector<Vector3d, Eigen::aligned_allocator<Vector3d>> VecVector3d;
typedef vector<Vector2d, Eigen::aligned_allocator<Vector2d>> VecVector2d;
typedef Matrix<double, 6, 1> Vector6d;

string p3d_file = "./p3d.txt";
string p2d_file = "./p2d.txt";

int main(int argc, char **argv) {

    VecVector2d p2d;
    VecVector3d p3d;
    Matrix3d K;
    double fx = 520.9, fy = 521.0, cx = 325.1, cy = 249.7;
    K << fx, 0, cx, 0, fy, cy, 0, 0, 1;

    // load points in to p3d and p2d
    // START YOUR CODE HERE
    ifstream p3d_fin(p3d_file);
    ifstream p2d_fin(p2d_file);

    Vector2d p2d_input;
    while(p2d_fin >> p2d_input(0) >> p2d_input(1))
    {
        p2d.push_back(p2d_input);
    }

    Vector3d p3d_input;
    while(p3d_fin >> p3d_input(0) >> p3d_input(1) >> p3d_input(2))
    {
        p3d.push_back(p3d_input);
    }

    // END YOUR CODE HERE
    assert(p3d.size() == p2d.size());

    int iterations = 100;
    double cost = 0, lastCost = 0;
    int nPoints = p3d.size();
    cout << "points: " << nPoints << endl;

    Sophus::SE3 T_esti; // estimated pose

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
            Vector4d TP4d = Sophus::SE3::exp(T_esti.log()).matrix() * p4d;
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

        T_esti = T_esti * Sophus::SE3::exp(dx);
        // END YOUR CODE HERE

        lastCost = cost;

        cout << "iteration " << iter << " cost=" << cout.precision(12) << cost << endl;
    }

    cout << "estimated pose: \n" << T_esti.matrix() << endl;
    return 0;
}
