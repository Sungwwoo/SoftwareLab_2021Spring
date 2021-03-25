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
	ifstream myData ("Beatles.wav", ios::binary | ios::in);
    if (!myData){
		cout << "Cannot access 'Beatles.wav'." << endl;
		return -1;
	}
    waveHeader myHeader;
	float f_s = (float)myHeader.sampleRate;
	int oneSecLength = myHeader.sampleRate * myHeader.numChannels;
	float *oneSecData = new float[oneSecLength];
	myData.read((char*)oneSecData, sizeof(float) * oneSecLength);
	myData.read((char*)oneSecData, sizeof(float) * oneSecLength);
	myData.read((char*)oneSecData, sizeof(float) * oneSecLength);
	myData.read((char*)oneSecData, sizeof(float) * oneSecLength);
	myData.read((char*)oneSecData, sizeof(float) * oneSecLength);
	myData.read((char*)oneSecData, sizeof(float) * oneSecLength);
	myData.read((char*)oneSecData, sizeof(float) * oneSecLength);
	cout << myHeader.sampleRate << " " << myHeader.numChannels << " " << oneSecLength << endl;
	int matrixSize = pow(2, 10);
	int arraySize = pow(matrixSize,2);
	int startPoint = oneSecLength - matrixSize * myHeader.numChannels - 100;
	ofstream out1 ("dataread.txt");
	
	float *inputData = new float [oneSecLength];
	for (int i = 0; i < oneSecLength; i ++){
		inputData[i] = oneSecData[startPoint + i * 2]; // 한 개 채널의 데이터만 변환하기 위해
	}
	for (int i = 0; i < matrixSize; i ++){
		out1 << inputData[i] << " ";
	}
	float *C = new float [arraySize];
	CreateHadamard(matrixSize, C);
	for (int i = 0; i < arraySize; i ++){
		C[i] = C[i] * 1 / sqrt(matrixSize);
	}

	float *result = new float [arraySize];
	MatrixMult(matrixSize, matrixSize, 1, result, oneSecData, result);
	ofstream out ("output.txt");
	for (int i = 0; i < arraySize; i ++){
		out << result[i] << " ";
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