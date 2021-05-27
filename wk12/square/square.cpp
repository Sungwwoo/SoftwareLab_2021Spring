#include <iostream>
#include <fstream>
#include <complex>
#include <cmath>
#include <chrono>
#include "FourierTransform.h"
using namespace std;
using namespace std::chrono;


int main() {

	int N = 1024;
	int calc = 1;
	FFT* fft;
	fft = new FFT(N);
	DFT* dft;
	dft = new DFT(N);

	// initializing x[n], X[k] to zero
	for (int n = 0; n < N; n++) {
		fft->x[n] = complex<double>(0.0, 0.0);
		fft->X[n] = complex<double>(0.0, 0.0);
		dft->x[n] = complex<double>(0.0, 0.0);
		dft->X[n] = complex<double>(0.0, 0.0);
	}

	ofstream signal("signal.txt");
	ofstream fwdFFT("ForwardFFT.txt");
	ofstream fwdDFT("ForwardDFT.txt");
	if (fwdFFT.fail() || signal.fail())
		return 2;

	// create x[n] for FFT and DFT
	for (int n = 0; n < 16; n++) {
		fft->x[n] = complex<double>(1.0, 0.0);
		dft->x[n] = complex<double>(1.0, 0.0);
	}
	for (int n = N - 15; n < N; n++) {
		fft->x[n] = complex<double>(1.0, 0.0);
		dft->x[n] = complex<double>(1.0, 0.0);
	}
	steady_clock::time_point startTime;
	steady_clock::time_point endTime;
	microseconds totalTime(0);
	microseconds avgTime;
	for (int i = 0; i < calc; i++) {
		if (i != calc - 1)
			cout << "\r" << i + 1 << " / " << calc;
		else 
			cout << "\r" << i + 1 << " / " << calc << endl;
		
		startTime = steady_clock::now();
		fft->ForwardFFT();
		endTime = steady_clock::now();
		totalTime += duration_cast<microseconds> (endTime - startTime);
	}
	avgTime = totalTime / calc;
	cout << "Average time elapsed on FFT: " << avgTime.count() << " us" << endl;

	totalTime = microseconds(0);
	for (int i = 0; i < calc; i++) {
		if (i != calc - 1)
			cout << "\r" << i + 1 << " / " << calc;
		else
			cout << "\r" << i + 1 << " / " << calc << endl;
		startTime = steady_clock::now();
		dft->ForwardDFT();
		endTime = steady_clock::now();
		totalTime += duration_cast<microseconds> (endTime - startTime);
	}
	avgTime = totalTime / calc;
	cout << "Average time elapsed on DFT: " << (duration_cast<milliseconds>(avgTime)).count() << " ms" << endl;

	for (int k = N / 2; k < N - 1; k++) {
		signal << fft->x[k].real() << endl;
		fwdFFT << fft->X[k].real() << endl;
		fwdDFT << dft->X[k].real() << endl;
	}
	for (int k = 0; k < N / 2 + 1; k++) {
		signal << fft->x[k].real() << endl;
		fwdFFT << fft->X[k].real() << endl;
		fwdDFT << dft->X[k].real() << endl;
	}
	signal.close();
	fwdFFT.close();

	cout << "Parseval's Theorem" << endl;
	cout << "FFT" << endl;
	complex<double> fft_sum_x(0.0, 0.0), fft_sum_X(0.0, 0.0), dft_sum_x(0.0, 0.0), dft_sum_X(0.0, 0.0);
	for (int i = 0; i < N; i++) {
		fft_sum_x += pow(abs(fft->x[i]),2);
		fft_sum_X += pow(abs(fft->X[i]), 2);
		dft_sum_x += pow(abs(dft->x[i]), 2);
		dft_sum_X += pow(abs(dft->X[i]), 2);
	}
	cout << fft_sum_x << " == " << fft_sum_X / (complex<double>)N << endl;
	cout << "DFT" << endl;
	cout << dft_sum_x << " == " << dft_sum_X / (complex<double>)N << endl;

	return 0;
}