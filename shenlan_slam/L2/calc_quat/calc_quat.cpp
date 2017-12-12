#include <iostream>
using namespace std;

#include <ctime>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>


int main( int argc, char** argv )
{
    // initilize values
    Eigen::Quaterniond q1(0.35, 0.2, 0.3, 0.1);
    Eigen::Quaterniond q2(-0.5, 0.4, -0.1, 0.2);
    Eigen::Quaterniond tmp;
    Eigen::Vector3d t1(0.3, 0.1, 0.1);
    Eigen::Vector3d t2(-0.1, 0.5, 0.3);
    Eigen::Vector3d p(0.5, 0.0, 0.2);
    Eigen::Vector3d p2;

    // normalized quaternion
    q1.normalize();
    q2.normalize();

    // init tmp
    tmp.w() = 0;
    tmp.vec() = p - t1;
    
    tmp = q1.inverse() * tmp * q1;
    tmp = q2 * tmp * q2.inverse();
    p2 = tmp.vec() + t2;

    cout << "coordinate of p2:" << endl << p2 << endl;

    return 0;
}
