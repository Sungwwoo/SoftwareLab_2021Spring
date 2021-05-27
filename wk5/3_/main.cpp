#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <Eigen/LU>
#include <cmath>
using namespace Eigen;
using namespace std;
void Polynomial(int order, int dataSize, double* x, double* y, double* coef);
double CalcError(int dataSize, double* y, double* y_fit);
bool CheckError(double error, double tolerance);

int main(){

	ifstream inputData("data2.txt");
	if (inputData.fail()){
		cout << "Cannot access 'data.txt'" << endl;
		return -1;
	}

	int dataSize;
	inputData >> dataSize;
	double *x = new double [dataSize];
	double *y = new double [dataSize];
	double *y_fit = new double[dataSize];

	for (int i = 0; i < dataSize; i ++){
		inputData >> x[i] >> y[i];
	}
	inputData.close();

	double error;
	double tolerance = 0.5;
	int order = 2;
	double* coef = new double [order + 1];
	Polynomial(order, dataSize, x, y, coef);
	for (int i = 0; i < dataSize; i ++){
		for (int j = 0; j < order; j ++){
		y_fit[i] += coef[j] * pow(x[i], j);
		}
	}
	error = CalcError(dataSize, y, y_fit);
	cout << error << endl; 

	/*
	ofstream outputData("result.txt");
	if (outputData.fail()){
		cout << "Cannot access 'result.txt'" << endl;
		return -1;
	}

	for (double i = -4; i <= 8; i += 0.01){
		outputData << i << " " << y_fit[i] << endl;
	}
	outputData.close();
	*/

	return 0;
}

void Polynomial(int order, int dataSize, double* x, double* y, double* coef){
	int size = order + 1;
	MatrixXd A(size, size);
	MatrixXd IA(size, size);
	MatrixXd B(size, 1), C(size, 1);

	double* sum_right = new double [2 * size - 1];
	// sum_right[0] = N, sum_right[1] = Nx, sum_right[2] = Nx^2, ..., sum_rignt[n] = Nx^n
	for (int i = 0; i < 2 * size - 1; i ++){
		for (int j = 0; j < dataSize; j ++){
			sum_right[i] += pow(x[j], i);
		}
	}
	
	for (int i = 0; i < size; i ++){
		for(int j = 0; j < size; j ++){
			A(i,j) = sum_right[i + j];
		}
	}


	double * sum_left = new double [size];
	// sum_left[0] = Ny, sum_left[1] = Nxy, sum_left[2] = Nx^2y, ..., sum_left[n] = Nx^ny
	for (int i = 0; i < size; i ++){
		for (int j = 0; j < dataSize; j ++){
			sum_left[i] += pow(x[j], i) * y[j];
		}
		
	}
	for (int i = 0; i < size; i ++){
		B(i) = sum_left[i];
	}

	IA = A.inverse();

	// C[0] = a_0, C[1] = a_1, ..., C[n] = a_n
	C = IA * B;
	
	cout << "Matrix A: " << endl;
	cout << A << endl << endl;
	cout << "Matrix B: " << endl;
	cout << B << endl << endl;
	cout << "Matrix C: " << endl;
	cout << C << endl << endl;

	// saving C
	for (int i = 0; i < size; i ++){
		coef[i] = C(i);
	}
}

double CalcError(int dataSize, double* y, double* y_fit){
	double error;
	for (int i = 0; i < dataSize; i ++){
		error += abs(y_fit[i] - y[i]) / y[i];
	}
	error = error / double(dataSize);

	return error;
}
