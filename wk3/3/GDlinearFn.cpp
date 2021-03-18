#include <fstream> // for FILE 
#include <iostream> 
using namespace std;
#include "GDlinearFn.h"

linearFn::linearFn(){
		N = 4;
		x = new float[N];
		y = new float[N];
		x[0] = 0.0; y[0] = 1.0;
		x[1] = -0.9; y[1] = -0.9;
		x[2] = 1.1; y[2] = 3.1;
		x[3] = 2.1; y[3] = 5.1;
}

linearFn::linearFn(const char *xx) {
	ifstream dataFile(xx);

	if (!dataFile)
		exit(666);

	dataFile >> N;
	//N = 4;// debug
	x = new float[N];
	y = new float[N];

	for (int i = 0; i < N; i++) 
		dataFile >> x[i] >> y[i];
	for (int i = 0; i < N; i++)
		cout << "Data: " << x[i] << " " << y[i] << endl;
}

// distance between (x,y) and projection point
float linearFn::SquaredDistance(float a, float b, float xx, float yy) {
	float p;
	p = (xx + a * yy - a * b) / (1 + a * a);
	return (xx - p) * (xx - p) + (yy - b - p * a) * (yy - b - p * a);
}

float linearFn::LossFn(float a, float b) {
	float sum = 0.0;
	for (int i = 0; i < N; i++) {
		sum += SquaredDistance(a, b, x[i], y[i]);
	}
	return sum;
}


float linearFn::dfabda(float a, float b, float da) { 
	cout << "dfabda: " << LossFn(a + da, b) << endl;
	cout << "dfabda: " << LossFn(a, b) << endl;
	return (LossFn(a + da, b) - LossFn(a, b)) / da; 
}

float linearFn::dfabdb(float a, float b, float db) {
	cout << "dfabdb: " << LossFn(a, b + db) << endl;
	cout << "dfabdb: " << LossFn(a, b) << endl;
	return (LossFn(a, b + db) - LossFn(a, b)) / db;
}
//float linearFn::EE(float, float, float, float) { ; }