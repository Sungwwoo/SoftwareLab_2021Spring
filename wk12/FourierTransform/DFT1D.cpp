#include "DFT1D.h"

DFT::DFT(int n) {
	N = n;
	x = new complex<double>[N];
	X = new complex<double>[N];
	expk = new complex<double>[N];

	double pi2N = 3.141592 * 2.0 / (double)N;
	for (int i = 0; i < N; i++) {
		expk[i] = exp(-complex<double>(0.0, 1.0) * pi2N * (double)i);
	}

}

DFT::~DFT() {
	delete[] x;
	delete[] X;
	delete[] expk;
}

void DFT::ForwardDFT() {
	complex<double> sum;
	for (int k = 0; k < N; k++) {
		sum = complex<double>(0.0, 0.0);
		for (int n = 0; n < N; n++) {
			sum += x[n] * pow(expk[k], n);
		}
		X[k] = sum;
	}
}
void DFT::InverseDFT() {
	complex<double> sum;

	for (int n = 0; n < N; n++) {
		sum = complex<double>(0.0, 0.0);
		for (int k = 0; k < N; k++) {
			sum += X[k] * pow(expk[k], -n);
		}
		x[n] = sum / (double)N;
	}
}