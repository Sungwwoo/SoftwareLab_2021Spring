#pragma once
#include <complex>

#define Real float

class FFT
{
	int N, NU;               // N = 2**NU
	void InitializeFFT();
	void DITFFT(int);       // 1-D decimation-in-time FFT
	std::complex<Real> *W;       // W[k] = exp(-2pi*k/N)

public:
	FFT(int);               // one dimensional constructor
	FFT(Real *, int);        // one dimensional constructor
	~FFT();

	std::complex<Real> *x, *X;   // x[n]  <-->  X[k]
	void ForwardFFT();  // x[n] ==> X[k]
	void InverseFFT();  // X[k] ==> x[n]
};
