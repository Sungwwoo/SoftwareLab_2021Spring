#include <iostream>
#include <fstream>
#include <complex>
#include <cmath>
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
	
	int x = 30 / 0.1;
	int y = N;
	unsigned char *mybmp = new unsigned char[x * y * 3];

	FFT spectrum(N);
	float fs = (float)myHeader.sampleRate;
	int unitSec = myHeader.sampleRate*myHeader.numChannels / 10; // 0.1초
	short *oneSec = new short[unitSec];
	int j = unitSec - N * myHeader.numChannels - 100;
	complex<float>* spectrumData = new complex<float>[N];
	int loc;
	complex<float> max = (0.0, 0.0);
	for (int t = 0; t < 900; t += 3){
		intputWave.read((char*)oneSec, sizeof(short)*unitSec);	
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
			spectrumData[i] = 20 * log10(abs(spectrum.X[i]));
			if (max < spectrumData[i])
				max = spectrumData[i];
		}
		
	}
	cout << max << endl;
	intputWave.close();
	
	return 0;
}