#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define PI 3.141592

void createData(ofstream& out, float freq, float sampleFreq, float amplitude);

int main(){
    // Sprint 1
    ofstream out1 ("Output.txt");

    if (!out1){
        cout << "Cannot access file 'Output.txt'." << endl;
        return -1;
    }

    for (int i=1; i<10; i++){
        out1 << "5 * " << i << " = " << 5 * i << endl;
    }

    // Sprint 2
    ofstream xx ("Output2.txt");

    if (!xx){
        cout << "Cannot access file 'Output2.txt'." << endl;
        return -1;
    }

    for (int n=0; n<=10; n++){
        xx << n <<  " " << pow(2, n) << endl;
    }

    // Sprint 3: In Excel
    // Sprint 4
    ofstream out2 ("Output4.txt");

    if (!out2){
        cout << "Cannot access file 'Output4.txt" << endl;
        return -1;
    }

    float f_s = 44100;
    float A = 10000;

    createData(out2, 220., f_s, A);
    createData(out2, 330., f_s, A);
    createData(out2, 440., f_s, A);
    createData(out2, 600., f_s, A);

    return 0;
}

void createData(ofstream& out, float freq, float sampleFreq, float amplitude){
    out << "Frequency " << freq << endl;
    float val;
    float dt = 1. / sampleFreq;

    for (float t=0; t<0.01; t+=dt){
        val = amplitude * sin(2 * PI * freq * t);
        out << t << "\t" << val << endl;
    }

    out << endl;
    cout << "Data created for frequency " << freq << endl;
}