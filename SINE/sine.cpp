#include <fstream>
#include <cmath>
using namespace std;

int main(){
    float pi = 3.141592;
    ofstream out ("output2.txt");
    float dt, xt, t = 0.0, f = 800., tmax = 0.1;

    dt = 1/8100.;
    for (float t = 0; t < tmax; t +=dt){
        out << t << " " << 1000. * sin(2 * pi * f * t) << endl;
    }

    out.close();
    return 0;
}