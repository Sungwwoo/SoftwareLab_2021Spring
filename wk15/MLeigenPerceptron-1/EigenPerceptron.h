#pragma once
#include <Eigen/Dense>
using namespace Eigen;
class Perceptrons {
public:
	int nIn;       // dimensions of input data
	VectorXd w;  // weight vector of perceptrons
	Perceptrons(int);
	int train(const VectorXd x, const int t, double learningRate);
	int predict(const VectorXd x);
private:
	int step(double);
};

