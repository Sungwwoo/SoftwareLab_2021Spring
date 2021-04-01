#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <Eigen/LU>
#include <cmath>
using namespace Eigen;
using namespace std;


void Polinomial(int order, int dataSize, double* x, double* y, double* y_fit, double* coef);
double CalcError(int dataSize, double* y, double* y_fit);

int main() {
	
	int maxIteration = 100; // Maximum value of order

	ifstream inputData("seoul_covid.txt");
	if (inputData.fail()){
		cout << "Cannot access input file" << endl;
		return 2;
	}
	int dataSize;
	inputData >> dataSize;
	double *x = new double [dataSize];
	double *y = new double [dataSize];
	double *y_fit = new double[dataSize];
	for (int i = 0; i < dataSize; i ++)
		inputData >> x[i] >> y[i];
	inputData.close();


	double error = 0;
	double priorError = 0;
	double tolerance = 1e-2;
	int order = 0;
	int optimalOrder = 0;
	int iteration = 0;
	
	while(1){
		order ++;
		iteration ++;
		double* coef = new double [order + 1];
		
		Polinomial(order, dataSize, x, y, y_fit, coef);
		error = CalcError(dataSize, y, y_fit);
		if (error < tolerance){
			cout << "Found " << order << "-th polinomial equation." << endl;
			cout << "C: [";
			for (int i = 0; i <= order; i ++){
				cout << coef[i] << " ";
			}
			cout << "]" << endl;
			break;
		}
		if (iteration == 1){
			priorError = error;
			optimalOrder = order;
		}

		cout << "Error of " << order << "-th polinomial equation: " << error << endl;

		if (error < priorError){
			priorError = error;
			optimalOrder = order;
		}

		if (isnan(error) | isinf(error) | iteration >= maxIteration){
			cout << endl;
			double* optimalCoef = new double [optimalOrder + 1];
			cout << "Found " << optimalOrder << "-th polinomial equation." << endl;
			Polinomial(optimalOrder, dataSize, x, y, y_fit, optimalCoef);
			cout << "C: [";
			for (int i = 0; i <= optimalOrder; i ++){
				cout << optimalCoef[i] << " ";
			}
			cout << "]" << endl;
			delete[] optimalCoef;
			delete[] coef;
			break;
		}

		delete[] coef;
	}


	ofstream outputData("seoul_result.txt");
	if (outputData.fail()){
		cout << "Cannot access output file." << endl;
		return 2;
	}
	
	for (int i = 0; i < dataSize; i ++){
		outputData << x[i] << " " << y[i] << " " << y_fit[i] <<endl;
	}
	outputData.close();
	
	return 0;
}

void Polinomial(int order, int dataSize, double* x, double* y, double* y_fit, double* coef){
	int size = order + 1;
	MatrixXd A(size, size);
	MatrixXd IA(size, size);
	MatrixXd B(size, 1), C(size, 1);

	for (int i = 0; i < dataSize; i ++){
		y_fit[i] = 0;
	}

	double* sum_right = new double [2 * size - 1];
	for (int i = 0; i < 2 * size - 1; i ++){
		sum_right[i] = 0;
	}
	double * sum_left = new double [size];
	for (int i = 0; i < size; i ++){
		sum_left[i] = 0;
	}
	
	// sum_right[0] = N, sum_right[1] = Nx, sum_right[2] = Nx^2, ..., sum_rignt[n] = Nx^n
	for (int i = 0; i < 2 * size - 1; i ++){
		for (int j = 0; j < dataSize; j ++){
			sum_right[i] += pow(x[j], (double)i);
		}
	}
	
	for (int i = 0; i < size; i ++){
		for(int j = 0; j < size; j ++){
			A(i,j) = sum_right[i + j];
		}
	}
	
	// sum_left[0] = Ny, sum_left[1] = Nxy, sum_left[2] = Nx^2y, ..., sum_left[n] = Nx^ny
	for (int i = 0; i < size; i ++){
		for (int j = 0; j < dataSize; j ++){
			sum_left[i] += (pow(x[j], (double)i) * y[j]);
		}
	}
	for (int i = 0; i < size; i ++){
		B(i) = sum_left[i];
	}
	IA = A.inverse();
	C = IA * B;
	// C[0] = a_0, C[1] = a_1, ..., C[n] = a_n

	for (int i = 0; i < size; i ++){
		coef[i] = C(i);
	}

	for (int i = 0; i < dataSize; i ++){
		for (int j = 0; j < order + 1; j ++){
			y_fit[i] += coef[j] * pow(x[i], (double)j);
		}
	}
	delete[] sum_right;
	delete[] sum_left;
}

double CalcError(int dataSize, double* y, double* y_fit){
	double error = 0;
	double avgError = 0;
	int count = 0;
	for (int i = 0; i < dataSize; i ++){
		if (y[i] == 0)
			continue;
		count ++;
		error += abs(y_fit[i] - y[i]) / abs(y[i]);
	}
	
	avgError = error / (double)count;

	return avgError;
}