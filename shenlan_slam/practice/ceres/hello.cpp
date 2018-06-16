#include <iostream>
#include <opencv2/core/core.hpp>
#include <ceres/ceres.h>
#include <chrono>

using namespace std;

// templated cost functor, implement residual r = 10 - x.
struct CostFunctor
{
    template<typename T>
    bool operator()(const T* const x, T* residual) const
    {
        residual[0] = T(10.0) - x[0];
        return true;
    }
};

struct NumericDiffCostFunctor
{
    bool operator()(const double* const x, double* residual) const
    {
        residual[0] = 10.0 - x[0];
        return true;
    }
};

int main(int argc, char** argv)
{
    double initial_x = 0.0;
    double x = initial_x;

    ceres::Problem problem;

    // auto diff
    ceres::CostFunction* cost_function = new ceres::AutoDiffCostFunction<CostFunctor, 1, 1>(new CostFunctor);

    // numerical diff
    // ceres::CostFunction* cost_function = new ceres::NumericDiffCostFunction<NumericDiffCostFunctor, ceres::CENTRAL, 1, 1> (new NumericDiffCostFunctor);

    problem.AddResidualBlock(cost_function, NULL, &x);

    ceres::Solver::Options options;
    options.minimizer_progress_to_stdout = true;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);

    cout << summary.BriefReport() << endl;
    cout << "x: " << initial_x << "->" << x << endl;
    return 0;
}
