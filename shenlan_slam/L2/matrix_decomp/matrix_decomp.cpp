#include <iostream>
using namespace std;

#include <ctime>
#include <Eigen/Core>
#include <Eigen/Dense>

#define MATRIX_SIZE 100

int main( int argc, char** argv )
{
    Eigen::MatrixXd matrix_x;

    Eigen::Matrix< double, MATRIX_SIZE, MATRIX_SIZE > matrix_NN;
    matrix_NN = Eigen::MatrixXd::Random( MATRIX_SIZE, MATRIX_SIZE );
    Eigen::Matrix< double, MATRIX_SIZE,  1> v_Nd;
    v_Nd = Eigen::MatrixXd::Random( MATRIX_SIZE,1 );

    // direct computation
    clock_t start = clock();
    Eigen::Matrix<double,MATRIX_SIZE,1> x = matrix_NN.inverse()*v_Nd;
    cout <<"time use in normal inverse is " << 1000* (clock() - start)/(double)CLOCKS_PER_SEC << "ms"<< endl;

    // QR decomposition
    start = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout <<"time use in QR decomposition is " <<1000*  (clock() - start)/(double)CLOCKS_PER_SEC <<"ms" << endl;

    // Cholesky decomposition
    start = clock();
    x = matrix_NN.llt().solve(v_Nd);
    cout <<"time use in LLT decomposition is " <<1000*  (clock() - start)/(double)CLOCKS_PER_SEC <<"ms" << endl;

    // LDLT decomposition
    start = clock();
    x = matrix_NN.ldlt().solve(v_Nd);
    cout <<"time use in LDLT decomposition is " <<1000*  (clock() - start)/(double)CLOCKS_PER_SEC <<"ms" << endl;

    return 0;
}
