#include "LogisticRegression.h"
#include "activation.h"

void LogisticRegression::train(MatrixXd& X, MatrixXd& T, int minibatchSize, double learningRate) {
	
		// train with SGD
		// 1. calculate gradient of W, b
		MatrixXd predicted_Y_;
		activation myAct;
		predicted_Y_ = myAct.softmax(X * W.transpose(), minibatchSize, nOut);
		
		dY = predicted_Y_ - T;
		grad_W = dY.transpose() * X;
		for (int i = 0; i < minibatchSize; i ++)
			for (int j = 0; j < nOut; j++)
				grad_b[j] += dY(i,j);
		// 2. update params
		W -= learningRate * grad_W / minibatchSize;
		b -= learningRate * grad_b / minibatchSize;
		//return dY;

}

MatrixXi LogisticRegression::predict(MatrixXd x) {
	activation myAct;
	MatrixXd y(x.rows(), nOut);
	
	y = myAct.softmax(x * W.transpose(), x.rows(), nOut);
	
	MatrixXi t; // output is the probability, so cast it to label
	t.resize(x.rows(), nOut);
	int argmax = -1;
	double max = 0.;

	for (int i = 0; i < x.rows(); i++){
		for (int j = 0; j < nOut; j++){
			if (max < y(i, j)) {
				max = y(i, j);
				argmax = j;
			}
		}
		for (int j = 0; j < nOut; j++){
			if (j == argmax)
				t(i,j) = 1;
			else
				t(i,j) = 0;
		}
	}
	return t;
}
