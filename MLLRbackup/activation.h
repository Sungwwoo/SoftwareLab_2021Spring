#pragma once
#include <Eigen/Dense>
using namespace Eigen;
class activation {
public:
	static int step(double x);
	static double sigmoid(double x);
	static MatrixXd softmax(MatrixXd x, int m, int n);
};
