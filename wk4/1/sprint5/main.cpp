#include <iostream>
#include <iomanip>
using namespace std;

void ShowMatrix(int M, int N, float *A);
void MatrixMult(int M, int N, int P, float *A, float *B, float *C);
void Transpose(int M, int N, float *A, float *AT);

int main(){
	// Sprint 5
	float C[]={	0.5, 0.5, 0.5, 0.5, 
				0.5, 0.5, -0.5, -0.5, 
				0.5, -0.5, -0.5 ,0.5, 
				0.5, -0.5, 0.5, -0.5};
	float CT[16];
	Transpose(4, 4, C, CT);
	
	float A1[4] = {100, 120, -4, 2};
	float A2[4] = {100, 20, 120, 32};
	float A3[4] = {10, 120, 108, 8};

	float CA1[4];
	MatrixMult(4, 4, 1, C, A1, CA1);
	ShowMatrix(4, 1, CA1);

	float CA2[4];
	MatrixMult(4, 4, 1, C, A2, CA2);
	ShowMatrix(4, 1, CA2);

	float CA3[4];
	MatrixMult(4, 4, 1, C, A3, CA3);
	ShowMatrix(4, 1, CA3);

	float CTA1[4];
	MatrixMult(4, 4, 1, CT, CA1, CTA1);
	ShowMatrix(4, 1, CTA1);

	float CTA2[4];
	MatrixMult(4, 4, 1, CT, CA2, CTA2);
	ShowMatrix(4, 1, CTA2);

	float CTA3[4];
	MatrixMult(4, 4, 1, CT, CA3, CTA3);
	ShowMatrix(4, 1, CTA3);

	// 결과의 의미?

	
	return 0;
}

void ShowMatrix(int M, int N, float *A){
	cout << "Printing Matrix: " << endl << endl;
	for (int m = 0; m < M; m ++){
		for (int n = 0; n < N; n ++){
			cout << setw(4) << A[m * N + n];
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