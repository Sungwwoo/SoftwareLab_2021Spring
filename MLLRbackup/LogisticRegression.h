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
	MatrixXd grad_W;
	VectorXd grad_b;
	MatrixXd dY;
	MatrixXd W;
	VectorXd b;
	
	LogisticRegression(int n, int nO,int mini) {
		nIn = n;
		nOut = nO;
		minibatchSize = mini;
		int i, j;

		W.resize(nOut,nIn);
		b.resize(nOut);
		for (i = 0; i < nOut; i++) {
			b[i] = 0.1;
			for (j = 0; j < nIn; j++)
				W(i, j) = 1.0;
		}
		
		grad_W.resize(nOut,nIn);
		grad_b.resize(nOut);
		for (i = 0; i < nOut; i++) {
			grad_b[i] = 0.0;
			for (j = 0; j < nIn; j++) 
				grad_W(i, j) = 0.0;
		}

		dY.resize(minibatchSize, nOut);
		//LogisticRegression(n, nO);
	}
	LogisticRegression(int n, int nO) {
		nIn = n;
		nOut = nO;
		int i, j;

		W.resize(nOut,nIn);
		b.resize(nOut);
		for (i = 0; i < nOut; i++) {
			b[i] = 0.1;
			for (j = 0; j < nIn; j++)
				W(i, j) = 1.0;
		}
		
		grad_W.resize(nOut,nIn);
		grad_b.resize(nOut);
		for (i = 0; i < nOut; i++) {
			grad_b[i] = 0.0;
			for (j = 0; j < nIn; j++) 
				grad_W(i, j) = 0.0; // initialize grad_W, grad_b
		}
		dY.resize(minibatchSize, nOut);
	}


	void train(MatrixXd& X, MatrixXd& T, int minibatchSize, double learningRate);
	MatrixXi predict(MatrixXd x);
};
