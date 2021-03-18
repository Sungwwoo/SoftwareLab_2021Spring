// Author: DY Suh
// Date : June 23, 2020
//
//  Gradient descend for line fitting
//  input : data1.txt     random data(almost linear) --> not working
//  input : 4 samples of the blank constructor --> working
//
//  Optimize for (a, b) of y = ax + b
//
#include <iostream> // for cout
#include <iomanip> // for setw()
#include <cmath>
#include "GDlinearFn.h"
using namespace std;

float EE(float x0, float y0, float x1, float y1){ 
	return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)); 
}

int main() {
	//linearFn ab((char*)"data1.txt");
	linearFn ab("data.txt");
	///// data done! //////////////
	float psi = 0.001, eta = 0.0001;	// for 4 sample (blank constructor)
	//float psi = 0.001, eta = 0.0001; 
	float da = 0.01, db = 0.01;
	float a0 = -2, b0 = 2;
	float a1 = -2.1, b1 = 0.8; 			// answer (a, b) = (1, 1)   blank constructor
	//float a1 = 1.1, b1 = 80.0;		// answer (a, b) = (1.2, 100)
	int iteration = 0;
	
	while (EE(a0, b0, a1, b1) > eta && iteration < 10000) {
		a0 = a1;
		b0 = b1;
		a1 -= psi * ab.dfabda(a0, b0, da);
		b1 -= psi * ab.dfabdb(a0, b0, db);
		cout << setw(10) << a0 << setw(10) << b0 << " >> " << setw(10) << a1 << setw(10) << b1 << endl;
		iteration++;
	}

	cout << iteration << "-th  E = " << EE(a0, b0, a1, b1) << endl;

	return 0;
}




