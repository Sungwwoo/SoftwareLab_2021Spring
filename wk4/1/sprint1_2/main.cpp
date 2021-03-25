#include <iostream>
#include <iomanip>
using namespace std;

// Sprint 1
void ShowMatrix(int M, int N, float *A);
// Sprint 2
void MatrixMult(int M, int N, int P, float *A, float *B, float *C);
// Sprint 4
void Transpose(int M, int N, float *A, float *AT);

int main(){
	// Sprint 1
	float A[] = {1, 2, 3, 4, 5, 6};
	float B[] = {1, 2, 3, 4};
	float C[4];

	ShowMatrix(2, 3, A);
	ShowMatrix(3, 2, A);

	// Sprint 2
	MatrixMult(3, 2, 2, A, B, C);
	ShowMatrix(3, 2, C);

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