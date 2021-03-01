#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define PI 3.141592

class waveHeader{
public:
    waveHeader() {};
    int chunckID, chunkSize, format, subChunk1ID, subChunk1size;
    short audioFormat, numChannels;
    int sampleRate, byteRate;
    short blockAlign, bitsPerSample;
    int subChunk2ID, subChunk2size;
};

int main(){
    
    ofstream myData ("mydata.wav", ios::binary | ios::out);
    
    short data[44100];
    int n = 44100;
    float dt = 1. / 44100.;
    float f = 440, A = 10000.;

    for (int i=0; i<44100; i++){
        float t = i * dt;
        data[i] = (short)(A * sin(2 * PI * f * t));
    }
    
    myData.write((char*) data, sizeof(short) * n);
    myData.close();

    ifstream xx("Beatles.wav", ios::binary | ios::in);
    ofstream myWave ("mywave.wav", ios::binary | ios::out);
    
    waveHeader myHeader;
    xx.read((char*)&myHeader, sizeof(waveHeader));
    cout << "NumChannels: " << myHeader.numChannels << endl;
    xx.close();

    myHeader.numChannels = 1;
    n = myHeader.sampleRate;
    cout << "NumChannels: " << myHeader.numChannels << endl;
    myWave.write((char*) &myHeader, sizeof(waveHeader));
    myWave.write((char*) data, sizeof(short) * n * myHeader.numChannels);
    myWave.close();

    return 0;
}