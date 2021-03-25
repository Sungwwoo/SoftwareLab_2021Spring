#include <iostream>
#include <iomanip>
using namespace std;

void ShowMatrix(int M, int N, float *A);
void MatrixMult(int M, int N, int P, float *A, float *B, float *C);
void Transpose(int M, int N, float *A, float *AT);

int main(){
	
	// Sprint 3
	float C[]={	0.5, 0.5, 0.5, 0.5, 
				0.5, 0.5, -0.5, -0.5, 
				0.5, -0.5, -0.5 ,0.5, 
				0.5, -0.5, 0.5, -0.5};
	float *C0, *C1, *C2, *C3;
	C0 = C; C1 = C + 4; C2 = C + 8; C3 = C + 12;
	float delta[16];
	
	MatrixMult(1, 4, 1, C0, C0, delta);
	MatrixMult(1, 4, 1, C0, C1, delta + 1);
	MatrixMult(1, 4, 1, C0, C2, delta + 2);
	MatrixMult(1, 4, 1, C0, C3, delta + 3);
	MatrixMult(1, 4, 1, C1, C0, delta + 4);
	MatrixMult(1, 4, 1, C1, C1, delta + 5);
	MatrixMult(1, 4, 1, C1, C2, delta + 6);
	MatrixMult(1, 4, 1, C1, C3, delta + 7);
	MatrixMult(1, 4, 1, C2, C0, delta + 8);
	MatrixMult(1, 4, 1, C2, C1, delta + 9);
	MatrixMult(1, 4, 1, C2, C2, delta + 10);
	MatrixMult(1, 4, 1, C2, C3, delta + 11);
	MatrixMult(1, 4, 1, C3, C0, delta + 12);
	MatrixMult(1, 4, 1, C3, C1, delta + 13);
	MatrixMult(1, 4, 1, C3, C2, delta + 14);
	MatrixMult(1, 4, 1, C3, C3, delta + 15);

	for (int i = 0; i < 4; i ++){
		for (int j = 0; j < 4; j ++){
			cout << "C" << i << " * " << "C" << j << " = " << delta[i * 4 + j] << endl;
		}
		cout << endl;
	}
	cout << endl;
	float CT[16];
	ShowMatrix(4, 4, C);
	Transpose(4, 4, C, CT);
	ShowMatrix(4, 4, CT);
	float result[16];
	MatrixMult(4, 4, 4, C, CT, result);
	ShowMatrix(4, 4, result);
	
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