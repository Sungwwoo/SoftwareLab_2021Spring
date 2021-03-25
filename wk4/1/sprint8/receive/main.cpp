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
	
	float receivedData1[4];
	ifstream out1 ("dat1.wav", ios::in | ios::binary);
	if (!out1){
		cout << "Cannot access file 'dat1.wav'." << endl;
		return -1;
	}
	out1.read((char*)receivedData1, sizeof(receivedData1));
	out1.close();
	float A1[4];
	MatrixMult(4, 4, 1, CT, receivedData1, A1);
	ShowMatrix(4, 1, A1);

	float receivedData2[4];
	ifstream out2 ("dat2.wav", ios::in | ios::binary);
	if (!out2){
		cout << "Cannot access file 'dat2.wav'." << endl;
		return -1;
	}
	out2.read((char*)receivedData2, sizeof(receivedData2));
	out2.close();
	float A2[4];
	MatrixMult(4, 4, 1, CT, receivedData2, A2);
	ShowMatrix(4, 1, A2);

	float receivedData3[4];
	ifstream out3 ("dat3.wav", ios::in | ios::binary);
	if (!out3){
		cout << "Cannot access file 'dat3.wav'." << endl;
		return -1;
	}
	out3.read((char*)receivedData3, sizeof(receivedData3));
	out3.close();
	receivedData3[3] = 0; receivedData3[1] = 0;
	float A3[4];
	MatrixMult(4, 4, 1, CT, receivedData3, A3);
	ShowMatrix(4, 1, A3);

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