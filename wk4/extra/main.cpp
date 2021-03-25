#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

#define PI 3.141592

float H2[4] = {1, 1, 1, -1};

void ShowMatrix(int M, int N, float *A);
void MatrixMult(int M, int N, int P, float *A, float *B, float *C);
void Transpose(int M, int N, float *A, float *AT);
void CreateHadamard(int N, float* A);

int main(){
	
	int matrixSize = pow(2, 8); // N 
	int arraySize = matrixSize * matrixSize;
	
	float dt = 0.01;
	float *inputSig = new float [matrixSize];
	
	
	ofstream out ("originalsignal.txt");

	for (int i = 0; i < matrixSize; i ++){
		inputSig[i] =100 * (sin(2 * PI * i * dt) + sin(4 * PI * i * dt) + sin(8 * PI * i * dt));
		out << i << "\t" << inputSig[i] << endl;
	}

	float *C = new float [arraySize];
	float *CA = new float [arraySize];
	CreateHadamard(matrixSize, C);
	for (int i = 0; i < arraySize; i ++){
		C[i] = C[i] * 1 / sqrt(matrixSize);
	}

	MatrixMult(matrixSize, matrixSize, 1, C, inputSig, CA);
	ofstream out2 ("transformedsignal1.txt");

	for (int i = 0; i < matrixSize; i ++){

		out2 << i << "\t" << CA[i] << endl;
	}
	int count = 0;
	for (int i = 0; i < matrixSize; i ++){
		if (abs(CA[i]) < 30){
			CA[i] = 0;
			count ++;
		}
	}
	cout << "Deleted " << count << " datas." << endl;
	ofstream out3 ("transformedsignal2.txt");

	for (int i = 0; i < matrixSize; i ++){

		out3 << i << "\t" << CA[i] << endl;
	}
	float *CT = new float [arraySize];
	float *result = new float [matrixSize];
	Transpose(matrixSize, matrixSize, C, CT);
	MatrixMult(matrixSize, matrixSize, 1, CT, CA, result);

	ofstream out4 ("reconstrutedsignal.txt");

	for (int i = 0; i < matrixSize; i ++){

		out4 << i << "\t" << result[i] << endl;
	}

	delete[] inputSig;
	delete[] C;
	delete[] CA;
	delete[] CT;
	delete[] result;
	
	return 0;
}

void ShowMatrix(int M, int N, float *A){
	cout << "Printing Matrix: " << endl << endl;
	for (int m = 0; m < M; m ++){
		for (int n = 0; n < N; n ++){
			cout <<  setw(4) << A[m * N + n];
		}
		cout << endl;
	}
	cout << endl;
}

void MatrixMult(int M, int N, int P, float *A, float *B, float *C){
	float sum;

	for (int m = 0; m < M; m ++){
		for (int p = 0; p < P; p ++){
			sum = 0;
			for (int n = 0; n < N; n ++){
				sum += A[m * N + n] * B[n * P + p];
			}
			C[m * P + p] = sum;
		}
	}
}

void Transpose(int M, int N, float *A, float *AT){
	for (int m = 0; m < M; m ++){
		for (int n = 0; n < N; n ++){
			AT[n * M + m] = A[m * N + n];
		}
	}
}

void CreateHadamard(int N, float* A){
	
	int size = pow(N/2, 2);
	float *HN = new float [size];

	if (N == 2)
		for (int i = 0; i < 4; i++)
			A[i] = H2[i];
	else{
		CreateHadamard(N/2, HN);
		for (int i = 0; i < N; i ++){
			for (int j = 0; j < N; j ++){
				A[i * N + j] = HN[(i % (N/2)) * N/2 + j % (N/2)];
				if ((i >= N / 2) & (j >= N / 2))
					A[i * N + j] = -HN[(i % (N/2)) * N/2 + j % (N/2)];	
			}
		}
	}
	delete[] HN;
	return;
}