#pragma once
#include <cmath>
#include <complex>
using namespace std;


class DFT {
public:
	int N;
	complex<double>* x, * X, * expk;
	DFT(int);
	~DFT();

	void ForwardDFT();
	void InverseDFT();
};