#pragma once
class Perceptrons {
public:
	int nIn;       // dimensions of input data
	double *w;  // weight vector of perceptrons
	Perceptrons(int nIn);
	int train(double *x, int t, double learningRate);
	int predict(double *x);
private:
	int step(double);
};

