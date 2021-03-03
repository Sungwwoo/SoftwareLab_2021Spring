#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define PI 3.141592

class waveHeader{
public:
    waveHeader() {};
    int chunckID, chunkSize, format, subChunk1ID, subChunk1Size;
    short audioFormat, numChannels;
    int sampleRate, byteRate;
    short blockAlign, bitsPerSample;
    int subChunk2ID, subChunk2Size;
};

int main(){
    // 
    ifstream xx("Beatles.wav", ios::binary | ios::in);
    waveHeader myHeader;
    xx.read((char*)&myHeader, sizeof(waveHeader));
    cout << myHeader.sampleRate << " " << myHeader.byteRate << " " << myHeader.bitsPerSample << endl;




    return 0;
}