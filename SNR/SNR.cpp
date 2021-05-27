#include <iostream>
#include <cmath>
using namespace std;

const float pi = 3.141592;

float fx (float t){
	return cos(2*pi*100*t) + 5*t;
}

float dfxdx_analytic (float t){
	return -2*pi*100*sin(2*pi*100*t) + 5;
}

float dfxdx_numeric (float t, float dt){
	return (fx(t + dt) - fx(t)) / dt;
}
int main(){
	float dt = 1./1000.;
	float signalPower = 0;
	float noisePower = 0;

	for (float t = 0; t < 1; t +=dt){
		signalPower += pow(abs(fx(t)),2);
		noisePower += pow(abs(dfxdx_numeric(t, dt) - fx(t)),2);
	}

	signalPower = signalPower / 1.;
	noisePower = noisePower / 1.;

	cout << "SNR is " << 10 * log10(signalPower / noisePower) << endl;
	return 0;
}