#pragma once
#include <complex>
using namespace std;

#define Real double

class FFT               
{
	int N,NU;            // N = 2**NU
	void InitializeFFT();
	void DITFFT(int);   // 1-D decimation-in-time FFT
	complex <double> *W;         // W[k] = exp(-2pi*k/N)

	public:
	FFT(int);               // one dimensional constructor
	FFT(Real *,int);        // one dimensional constructor
	~FFT();

	void ForwardFFT();  // x[n] ==> X[k]
	void InverseFFT();  // X[k] ==> x[n]
	complex <double> *x,*X;
};

class DFT {
public:
	int N;
	complex<double>* x, * X, * expk;
	DFT(int);
	~DFT();

	void ForwardDFT();
	void InverseDFT();
};
