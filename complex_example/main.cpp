#include <fstream>
#include <complex>
#include <cmath>
using namespace std;

const float tp = 0.125664;

int main(){
    ofstream out ("output.txt");

    complex<float> z[100], zo;
    zo = complex<float>(cos(tp), sin(tp)) * complex<float>(pow(3.0, 0.01), 0.0);

    z[0] = complex<float>(1.0, 0.0);
    for (int i = 1; i < 100; i++){
        z[i] = z[i-1] * zo;
    }
    for (int i = 0; i < 100; i++){
        out << z[i].real() << " " << z[i].imag() << endl;
    }
}