#include <iostream>
#include <fstream>
#include <list>
#include <random>
#include <Eigen/Dense>
#include "LogisticRegression.h"
using namespace std;
using namespace std;

int * shuffle(int N);
int main() {
	int patterns = 2;   // number of classes
	int train_N = 800; // 400 * patterns;
	int test_N = 120;   // 60 * patterns;
	int nIn = 2;
	int nOut = 2;
  	// Declare variables and constants
	MatrixXd train_X;
	train_X.resize(train_N, nIn);
	MatrixXd train_T;
	train_T.resize(train_N, nOut);
	

	MatrixXd test_X;
	MatrixXd test_T;
	MatrixXi predicted_T;
	test_X.resize(test_N, nIn);
	test_T.resize(test_N, nOut);
	predicted_T.resize(test_N, nOut);

	int epochs = 10000;
	double learningRate = 0.2;

	int minibatchSize = train_N;  
	int minibatch_N = train_N / minibatchSize; 


	default_random_engine generator;
	normal_distribution<double> g1(-2.0, 1.0);
	normal_distribution<double> g2(2.0, 1.0);
	normal_distribution<double> g3(0.0, 1.0);

	ofstream out("LRdata60X3test.txt");
	if (out.fail())
		cout << "File open error" << endl;
	// data set in class 1
	for (int i = 0; i < train_N / patterns ; i++) {
		train_X(i, 0) = g1(generator);
		train_X(i, 1) = g2(generator);
		train_T(i, 0) = 1; 
		train_T(i, 1) = 0; 
	}
	for (int i = 0; i < test_N / patterns; i++) {
		test_X(i, 0) = g1(generator);
		test_X(i, 1) = g2(generator);
		test_T(i, 0) = 1; 
		test_T(i, 1) = 0; 
		out << test_X(i, 0) << "    " << test_X(i, 1) << endl;
	}
	// data set in class 2
	for (int i = 0; i < train_N / patterns ; i++) {
		train_X(i, 0) = g3(generator);
		train_X(i, 1) = g3(generator);
		train_T(i, 0) = 0; 
		train_T(i, 1) = 1; 
	}
	for (int i = 0; i < test_N / patterns; i++) {
		test_X(i, 0) = g3(generator);
		test_X(i, 1) = g3(generator);
		test_T(i, 0) = 0; 
		test_T(i, 1) = 1;
		out << test_X(i, 0) << "    " << test_X(i, 1) << endl;
	}
	out.close();
	LogisticRegression classifier = LogisticRegression(nIn, nOut, minibatchSize);
	cout << "(nIn nOut mini)" << classifier.nIn << " " << classifier.nOut << " " << classifier.minibatchSize << "\n";

	// train
	for (int epoch = 0; epoch < epochs; epoch++) {
		cout << epoch << " / " << epochs << "\r";
		classifier.train(train_X, train_T, minibatchSize, learningRate);
		learningRate *= 0.95;
	}
	
	// test
	predicted_T = classifier.predict(test_X);
	//
	// Evaluate the model
	//
	cout << predicted_T << endl;
	MatrixXd confusionMatrix;
	VectorXd precision;
	VectorXd recall;
	confusionMatrix.resize(patterns, patterns);
	precision.resize(patterns);
	recall.resize(patterns);
	double accuracy = 0;

	for (int i = 0; i < patterns; i++) {
		precision[i] = recall[i] = 0;

		for (int j = 0; j < patterns; j++)
			confusionMatrix(i, j) = 0;
	}

	for (int i = 0; i < test_N; i++) {
		int predicted_,actual_;
		for (predicted_ = 0; predicted_<patterns; predicted_++) 
			if (predicted_T(i, predicted_) == 1)
				break;
		for (actual_ = 0; actual_<patterns; actual_++) 
			if (test_T(i, actual_) == 1) 
				break;

		confusionMatrix(actual_, predicted_) += 1.;
	}

	for (int i = 0; i < patterns; i++) {
		double col_ = 0.;
		double row_ = 0.;

		for (int j = 0; j < patterns; j++) {

			if (i == j) {
				accuracy += confusionMatrix(i, j);
				precision[i] += confusionMatrix(i, j);
				recall[i] += confusionMatrix(i, j);
			}

			col_ += confusionMatrix(i, j);
			row_ += confusionMatrix(i, j);
		}
		precision[i] /= col_;
		recall[i] /= row_;
	}

	accuracy /= test_N;

	cout << "------------------------------------\n";
	cout << "Logistic Regression model evaluation\n";
	cout << "------------------------------------\n";
	cout << "Accuracy: " << accuracy * 100 << "\n";
	cout << "Precision:\n";
	for (int i = 0; i < patterns; i++) {
		cout << " class "<< i+1<< ":"  << precision[i] * 100 << "\n";
	}
	cout << "Recall:\n";
	for (int i = 0; i < patterns; i++) {
		cout << " class " << i + 1 << ":" << recall[i] * 100 << "\n";
	}
	
	return 0;
}