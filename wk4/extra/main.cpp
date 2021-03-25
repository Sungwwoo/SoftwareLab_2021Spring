#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

float H2[4] = {1, 1, 1, -1};
class waveHeader{
public:
    waveHeader() {};
    int chunckID, chunkSize, format, subChunk1ID, subChunk1size;
    short audioFormat, numChannels;
    int sampleRate, byteRate;
    short blockAlign, bitsPerSample;
    int subChunk2ID, subChunk2size;
};
void ShowMatrix(int M, int N, float *A);
void MatrixMult(int M, int N, int P, float *A, float *B, float *C);
void Transpose(int M, int N, float *A, float *AT);
void CreateHadamard(int N, float* A);

int main(){
	
    waveHeader myHeader;
	float f_s = (float)myHeader.sampleRate;
	float dt = 1/f_s;
	
	ifstream myData ("Beatles.wav", ios::binary | ios::in);
    if (!myData){
		cout << "Cannot access 'Beatles.wav'." << endl;
		return -1;
	}
	myData.read((char*)&myHeader, sizeof(waveHeader));

	int oneSecLength = myHeader.sampleRate * myHeader.numChannels; // 1초 길이

	float *stereoData = new float[oneSecLength];

	myData.read((char*)stereoData, sizeof(float) * oneSecLength);

	int matrixSize = pow(2, 6); // N
	int arraySize = matrixSize * matrixSize; // N^2

	ofstream out1 ("dataread.txt");

	float *monoData = new float [arraySize];
	for (int i = 0; i < arraySize * 2; i ++){
		if (i % 2 == 0)
			monoData[i / 2] = stereoData[i]; // 한 개 채널의 데이터 분리
	}

	for (int i = 0; i < arraySize; i ++){
		out1 << monoData[i] << " ";
	}

	float *C = new float [arraySize];
	CreateHadamard(matrixSize, C);

	// normalize
	for (int i = 0; i < arraySize; i ++){
		C[i] = C[i] * (1 / sqrt(matrixSize));
	}
	
	float *result = new float [arraySize];

	MatrixMult(matrixSize, matrixSize, matrixSize, C, monoData, result);

	ofstream out ("output.txt");
	for (int i = 0; i < arraySize; i ++){
		// i 자리에 어떤거?
		out << i << " " << abs(result[i]) << endl;
	}

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