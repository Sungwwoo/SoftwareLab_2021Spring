#include <iostream>
#include <fstream>
#include <complex> 
#include "fft1d.h"
#include "bmpNew.h"
const int N = 1024;
using namespace std;

class waveHeader {
public:
	waveHeader() {};
	int chunkID, chunkSize, Format, subChunkID, subChunk1size;
	short	audioFormat, numChannels;
	int sampleRate, byteRate;
	short blockAlign, bitsPerSample;
	int subChunk2ID, subChunk2size;
};

int main() {
	ifstream intputWave("Beatles.wav", ios::binary | ios::in);
	if (intputWave.fail())
		return 2;

	waveHeader myHeader;
	intputWave.read((char*)&myHeader, sizeof(waveHeader));
	cout << "   sampleRate = " << myHeader.sampleRate << endl;    // 22050
	cout << "   numChannels = " << myHeader.numChannels << endl;  // 2
	cout << "   bitsPerSample = " << myHeader.bitsPerSample << endl; // 16
	cout << "   data size = " << myHeader.sampleRate * myHeader.numChannels * myHeader.bitsPerSample / 8 << endl;

	FFT spectrum(N);
	float fs = (float)myHeader.sampleRate;
	int n1sec = myHeader.sampleRate*myHeader.numChannels;
	short *oneSec = new short[n1sec];
	intputWave.read((char*)oneSec, sizeof(short)*n1sec);
	intputWave.read((char*)oneSec, sizeof(short)*n1sec);
	intputWave.read((char*)oneSec, sizeof(short)*n1sec);
	int j = n1sec - N * myHeader.numChannels - 100;
	ofstream output("spectrum.txt");
	
	if (myHeader.numChannels == 2){
		for (int i = 0; i < N; i++) {
			spectrum.x[i] = complex<float>((float)oneSec[j+i*2],0.0);
		}
	}
	else{
		for (int i = 0; i < N; i++) {
			spectrum.x[i] = complex<float>((float)oneSec[i],0.0);
		}
	}

	spectrum.ForwardFFT();
	for (int i = 0; i < N; i++) {
		output  << (float)i / fs << " " << spectrum.x[i].real() << " " << (float)i / (float)N * fs << " " << abs(spectrum.X[i])* abs(spectrum.X[i]) << endl;
	}
	output.close();
	intputWave.close();
	
	return 0;
}