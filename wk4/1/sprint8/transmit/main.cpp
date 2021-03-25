#include <iostream>
#include <iomanip>
#include <fstream>
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
	CA1[2] = 0; CA1[3] = 0;

	float CA2[4];
	MatrixMult(4, 4, 1, C, A2, CA2);
	ShowMatrix(4, 1, CA2);
	CA2[1] = 0; CA2[2] = 0;
	
	float CA3[4];
	MatrixMult(4, 4, 1, C, A3, CA3);
	ShowMatrix(4, 1, CA3);
	CA3[1] = 0; CA3[3] = 0;

	ofstream out1 ("dat1.wav", ios::out | ios::binary);
	if (!out1){
		cout << "Cannot access file 'dat1.wav'." << endl;
		return -1;
	}
	out1.write((char*)CA1, sizeof(CA1));
	out1.close();

	ofstream out2 ("dat2.wav", ios::out | ios::binary);
	if (!out2){
		cout << "Cannot access file 'dat2.wav'." << endl;
		return -1;
	}
	out2.write((char*)CA2, sizeof(CA2));
	out2.close();
	
	ofstream out3 ("dat3.wav", ios::out | ios::binary);
	if (!out3){
		cout << "Cannot access file 'dat3.wav'." << endl;
		return -1;
	}
	cout << sizeof(CA3) << " " << 4 * sizeof(float) << endl;
	out3.write((char*)CA3, sizeof(CA3));
	out3.close();

	
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