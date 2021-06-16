#pragma once
#include <Eigen/Dense>
#include <iostream> // debug
using namespace std; // debug
using namespace Eigen;

class LogisticRegression {
public:
	int nIn;
	int nOut;
	int minibatchSize = 50;
// private
	MatrixXd grad_W; // = new double[nOut][nIn];
	VectorXd grad_b; // = new double[nOut];
	MatrixXd dY; // = new double[minibatchSize][nOut];
	MatrixXd W;
	VectorXd b;
	
	LogisticRegression(int n, int nO,int mini) {;
		nIn = n;
		nOut = nO;
		minibatchSize = mini;
		int i, j;

		W.resize(nOut, nIn);
		b.resize(nOut);
		for (i = 0; i < nOut; i++) {
			b[i] = 0.1;
			for (j = 0; j < nIn; j++) 
				W(i, j) = 1.0; // initialize W, b
		}
		
		grad_W.resize(nOut, nIn);  
		grad_b.resize(nOut);
		for (i = 0; i < nOut; i++) {
			grad_b[i] = 0.0;
			for (j = 0; j < nIn; j++) 
				grad_W(i, j) = 0.0; // initialize grad_W, grad_b
		}

		dY.resize(minibatchSize, nOut);
		//LogisticRegression(n, nO);
	}
	LogisticRegression(int n, int nO) {
		nIn = n;
		nOut = nO;
		int i, j;

		W.resize(nOut, nIn);
		b.resize(nOut);
		for (i = 0; i < nOut; i++) {
			b[i] = 0.1;
			for (j = 0; j < nIn; j++) 
				W(i, j) = 1.0; // initialize W, b
		}
		
		grad_W.resize(nOut, nIn);  
		grad_b.resize(nOut);
		for (i = 0; i < nOut; i++) {
			grad_b[i] = 0.0;
			for (j = 0; j < nIn; j++) 
				grad_W(i, j) = 0.0; // initialize grad_W, grad_b
		}

		dY.resize(minibatchSize, nOut);

	}
	void train(MatrixXd X, MatrixXi T, int minibatchSize, double learningRate);
	VectorXd output(VectorXd x); 
	VectorXi predict(VectorXd x);
};
