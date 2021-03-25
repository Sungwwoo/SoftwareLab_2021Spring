#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

float H2[4] = {1, 1, 1, -1};

void ShowMatrix(int M, int N, float *A);
void MatrixMult(int M, int N, int P, float *A, float *B, float *C);
void Transpose(int M, int N, float *A, float *AT);
void CreateHadamard(int N, float* A);

int main(){
	float value = 1;
	float C0[8] = {value, value, value, value, value, value, value, value};
	float C1[8] = {value, value, value, value, -value, -value, -value, -value};
	float C2[8] = {value, value, -value, -value, -value, -value, value, value};
	float C3[8] = {value, value, -value, -value, value, value, -value, -value};

	float delta[16];
	MatrixMult(1, 8, 1, C0, C0, delta);
	MatrixMult(1, 8, 1, C0, C1, delta + 1);
	MatrixMult(1, 8, 1, C0, C2, delta + 2);
	MatrixMult(1, 8, 1, C0, C3, delta + 3);
	MatrixMult(1, 8, 1, C1, C0, delta + 4);
	MatrixMult(1, 8, 1, C1, C1, delta + 5);
	MatrixMult(1, 8, 1, C1, C2, delta + 6);
	MatrixMult(1, 8, 1, C1, C3, delta + 7);
	MatrixMult(1, 8, 1, C2, C0, delta + 8);
	MatrixMult(1, 8, 1, C2, C1, delta + 9);
	MatrixMult(1, 8, 1, C2, C2, delta + 10);
	MatrixMult(1, 8, 1, C2, C3, delta + 11);
	MatrixMult(1, 8, 1, C3, C0, delta + 12);
	MatrixMult(1, 8, 1, C3, C1, delta + 13);
	MatrixMult(1, 8, 1, C3, C2, delta + 14);
	MatrixMult(1, 8, 1, C3, C3, delta + 15);

	ShowMatrix(4, 4, delta);

	float C[256];
	CreateHadamard(16, C);
	ShowMatrix(16, 16,  C);
	for (int i = 0; i < 256; i ++){
		C[i] = C[i] * 1 / 4;
	}
	float CT[256];
	Transpose(16, 16, C, CT);
	float result[256];
	MatrixMult(16, 16, 16, C, CT, result);
	ShowMatrix(16, 16,  result);
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

	if (N % 2 != 0){
		cout << "N must be power of 2." << endl;
		return;
	}

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