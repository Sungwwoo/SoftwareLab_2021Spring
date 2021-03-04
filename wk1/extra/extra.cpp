#include <fstream>
#include <iostream>
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
    
    ofstream myWave ("airplane.wav", ios::binary | ios::out);
    ifstream xx("Beatles.wav", ios::binary | ios::in);

    if (!myWave){
        cout << "Cannot access file." << endl;
        return -1;
    }
    if (!xx){
        cout << "Cannot access file." << endl;
        return -1;
    }
    waveHeader myHeader;
    xx.read((char*)&myHeader, sizeof(waveHeader));
    xx.close();
    
    myHeader.numChannels = 1;
    int n = myHeader.sampleRate;
    cout << n << endl;
    float dt = 1. / 44100.;
    float A = 10000.;
    float t;
    
    // 도
    float f = 261.626;
    short dataC[44100];
    for (int i=0; i<n; i++){
        t = i * dt;
        dataC[i] = (short)(A * sin(2 * PI * f * t));
    }
    
    // 레
    f = 293.665;
    short dataD[44100];
    for (int i=0; i<n; i++){
        t = i * dt;
        dataD[i] = (short)(A * sin(2 * PI * f * t));
    }

    // 미
    f = 329.627;
    short dataE[44100];
    for (int i=0; i<n; i++){
        t = i * dt;
        dataE[i] = (short)(A * sin(2 * PI * f * t));
    }

    short data[44100 * 7];
    for (int i=0; i<7*n; i++){
        if (i < n)                          // 미
            data[i] = dataE[i];
        else if (i < 2 * n)                 // 레
            data[i] = dataD[i % n];
        else if (i < 3 * n)                 // 도
            data[i] = dataC[i % n];
        else if (i < 4 * n)                 // 레
            data[i] = dataD[i % n];
        else                                // 미 3번
            if (i % n > 40000)
                data[i] = 0;
            else
                data[i] = dataE[i % n];
    }
    myWave.write((char*) &myHeader, sizeof(waveHeader));
    myWave.write((char*) data, sizeof(short) * 7 * n * myHeader.numChannels);

    myWave.close();

    return 0;
}