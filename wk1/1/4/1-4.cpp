#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define PI 3.141592

int main(){
    ofstream out1("220.txt");
    ofstream out2("330.txt");
    ofstream out3("440.txt");
    ofstream out4("600.txt");

    if (!out1 || !out2 || !out3 || !out4){
        cout << "Cannot open file." << endl;
        return -1;
    }
    
    float f_s = 44100;
    float dt = 1 / f_s;
    float A = 10000;
    float val;

    float f = 220;
    for (float t=0; t<0.01; t+=dt){
        val = sin(2 * PI * f * t);
        out1 << t << " " << val << endl;
    }

    f = 330;
    for (float t=0; t<0.01; t+=dt){
        val = sin(2 * PI * f * t);
        out2 << t << " " << val << endl;
    }

    f = 440;
    for (float t=0; t<0.01; t+=dt){
        val = sin(2 * PI * f * t);
        out3 << t << " " << val << endl;
    }

    f = 600;
    for (float t=0; t<0.01; t+=dt){
        val = sin(2 * PI * f * t);
        out4 << t << " " << val << endl;
    }
    return 0;
}