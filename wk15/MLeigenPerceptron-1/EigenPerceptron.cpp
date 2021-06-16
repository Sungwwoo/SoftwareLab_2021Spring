#include "EigenPerceptron.h"
Perceptrons::Perceptrons(int n) {
	nIn = n;
	w.resize(nIn);
	for(int i = 0; i<nIn;i++) w[i] = 0.1; // suh   이걸 넣으니 45%에서 100%로 바뀐다. 
}

int Perceptrons::train(const VectorXd x, const int t, double learningRate) {
	// check if the data is classified correctly
	if (w.dot(x) * t > 0) return 1;
	// apply steepest descent method if the data is wrongly classified
	else	w += learningRate * x * t;	
	return 0;
}
int Perceptrons::predict(const VectorXd x) {
	return step(w.dot(x));
}
int Perceptrons::step(double x) {
	if (x > 0) return 1;
	return -1;
}
