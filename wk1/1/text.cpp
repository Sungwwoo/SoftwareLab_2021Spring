#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define PI 3.141592

void writeMultTable(ofstream & out, int times);
void writePower(ofstream & out, int base);
void createData(ofstream& out, float freq, float sampleFreq, float amplitude);

int main(){
    // Sprint 1
    ofstream out1 ("Output.txt");

    if (!out1){
        cout << "Cannot access file 'Output.txt'." << endl;
        return -1;
    }

    // 구구단 5단 작성
    writeMultTable(out1, 5);

    // Sprint 2
    ofstream xx ("Output2.txt");

    if (!xx){
        cout << "Cannot access file 'Output2.txt'." << endl;
        return -1;
    }

    // 2의 제곱수 작성
    writePower(xx, 2);

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

    // Extra
    ofstream out3 ("LowSampling.txt");

    if (!out3){
        cout << "Cannot access file 'LowSampling.txt" << endl;
        return -1;
    }

    f_s = 1200;
    createData(out3, 220., f_s, A);
    createData(out3, 330., f_s, A);
    createData(out3, 440., f_s, A);
    createData(out3, 600., f_s, A);

    ofstream out4 ("LowSampling2.txt");

    if (!out4){
        cout << "Cannot access file 'LowSampling2.txt" << endl;
        return -1;
    }

    f_s = 6000;
    createData(out4, 220., f_s, A);
    createData(out4, 330., f_s, A);
    createData(out4, 440., f_s, A);
    createData(out4, 600., f_s, A);

    return 0;
}

void writeMultTable(ofstream & out, int times){
    for (int i=1; i<10; i++){
        out << times << " * " << i << " = " << times * i << endl;
    }
}

void writePower(ofstream & out, int base){
    for (int n=0; n<=10; n++){
        out << n <<  " " << pow(base, n) << endl;
    }
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
    cout << "Data created for frequency " << freq << " with sampling frequency " << sampleFreq << endl;
}