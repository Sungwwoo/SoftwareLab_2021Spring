#include <iostream>
#include <iomanip>
using namespace std;

void ShowMatrix(int M, int N, float *A);
void MatrixMult(int M, int N, int P, float *A, float *B, float *C);
void Transpose(int M, int N, float *A, float *AT);

int main(){
	// Sprint 5  데이터 압축 (mp3에서 쓰이는 방식)
	float C[]={	0.5, 0.5, 0.5, 0.5, 
				0.5, 0.5, -0.5, -0.5, 
				0.5, -0.5, -0.5 ,0.5, 
				0.5, -0.5, 0.5, -0.5};
	float CT[16];
	Transpose(4, 4, C, CT);
	
	float A1[4] = {100, 120, 0, 0};
	float A2[4] = {100, 0, 120, 0};
	float A3[4] = {0, 120, 108, 0};

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

	// A 벡터들의 작은 값 2개씩 없앴음에도 결과값은 큰 차이가 없음 -> 전송하는 데이터는 감소하지만 왜곡은 적다 (압축하여 전송해도 손실이 적다)

	
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