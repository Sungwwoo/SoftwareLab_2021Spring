#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define PI 3.141592

// Global Variables
float dx = 0.01, dy = 0.01;

// Functions
float fxy(float x, float y);
float dfxydx(float x, float y, float dx);
float dfxydy(float x, float y, float dy);
float EE(float x0, float y0, float x1, float y1);
void GradientDescent(const char* fileName, float xi0, float yi0, float xi1, float yi1, float psi, float eta);
void GradientAscent(const char* fileName, float xi0, float yi0, float xi1, float yi1, float psi, float eta);


int main(){
	// Sprint 1
	ofstream out ("excelvalues.txt");
	out << "Maxima: \nfxy(0.25, 0.15) = " << fxy(0.25, 0.15) << endl;
	out << "fxy(0.25, 0.65) = " << fxy(0.25, 0.65) << endl;
	out << "fxy(0.75, 0.40) = " << fxy(0.75, 0.4) << endl;
	out << "fxy(0.75, 0.90) = " << fxy(0.75, 0.9) << endl;
	out << "Minima: \nfxy(0.25, 0.40) = " << fxy(0.25, 0.4) << endl;
	out << "fxy(0.25, 0.90) = " << fxy(0.25, 0.9) << endl;
	out << "fxy(0.75, 0.15) = " << fxy(0.75, 0.15) << endl;
	out << "fxy(0.75, 0.65) = " << fxy(0.75, 0.65) << endl;

	// Sprint 3
	float psi = 0.005, eta = 0.01;	// step size, accuracy

	// Gradiend Descent
	// 1. fxy(0.25, 0.4)
	float xi1 = 0.3, yi1 = 0.6;
	float xi0 = 0.0, yi0 = 0.0;
	GradientDescent("descent1.txt", xi0, yi0, xi1, yi1, psi, eta);
	
	// 2. fxy(0.25, 0.90)
	xi1 = 0.3, yi1 = 0.9;
	xi0 = 0.0, yi0 = 0.8;
	GradientDescent("descent2.txt", xi0, yi0, xi1, yi1, psi, eta);

	// 3. fxy(0.75, 0.15)
	xi1 = 0.8, yi1 = 0.3;
	xi0 = 0.4, yi0 = 0.0;
	GradientDescent("descent3.txt", xi0, yi0, xi1, yi1, psi, eta);

	// 4. fxy(0.75, 0.65)
	xi1 = 0.8, yi1 = 0.8;
	xi0 = 0.4, yi0 = 0.4;
	GradientDescent("descent4.txt", xi0, yi0, xi1, yi1, psi, eta);


	// Gradient Ascent
	// 1. fxy(0.25, 0.15)
	xi1 = 0.3, yi1 = 0.1;
	xi0 = 0.0, yi0 = 0.0;
	GradientAscent("ascent1.txt", xi0, yi0, xi1, yi1, psi, eta);

	// 2. fxy(0.25, 0.65)
	xi1 = 0.4, yi1 = 0.46;
	xi0 = 0.0, yi0 = 0.8;
	GradientAscent("ascent2.txt", xi0, yi0, xi1, yi1, psi, eta);

	// 3. fxy(0.75, 0.40)
	xi1 = 0.9, yi1 = 0.5;
	xi0 = 0.7, yi0 = 0.0;
	GradientAscent("ascent3.txt", xi0, yi0, xi1, yi1, psi, eta);

	// 4. fxy(0.75, 0.90)
	xi1 = 0.9, yi1 = 0.9;
	xi0 = 0.7, yi0 = 0.0;
	GradientAscent("ascent4.txt", xi0, yi0, xi1, yi1, psi, eta);

	return 0;
}

// Functions 
float fxy(float x, float y){
	return sin(2 * PI * x) * sin(4 * PI * y);
}

float dfxydx(float x, float y, float dx){
	return (fxy(x + dx, y) - fxy(x,y)) / dx;
}

float dfxydy(float x, float y, float dy){
	return (fxy(x, y + dy) - fxy(x,y)) / dy;
}

float EE(float x0, float y0, float x1, float y1){
	return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));	// l_2 norm
}

void GradientDescent(const char* fileName, float xi0, float yi0, float xi1, float yi1, float psi, float eta){
	int iteration = 0;
	ofstream out (fileName);

	if (!out){
		cout << "Cannot access file '" << fileName << "'." << endl;
		exit(-1);
	}

	while (EE(xi0, yi0, xi1, yi1) > eta && iteration < 1000){
		xi0 = xi1;
		yi0 = yi1;
		xi1 -= psi * dfxydx(xi0, yi0, dx);
		yi1 -= psi * dfxydy(xi0, yi0, dy);

		out << xi0 << "\t" << yi0 << "\t>>" << xi1 << "\t" << yi1 << endl;
		iteration++;
	}
	
	out << iteration << "-th E = " << EE(xi0, yi0, xi1, yi1) << endl;
	out << "Minimum Founded: " << fxy(xi1, yi1) << endl;
}

void GradientAscent(const char* fileName, float xi0, float yi0, float xi1, float yi1, float psi, float eta){
	int iteration = 0;
	ofstream out (fileName);

	if (!out){
		cout << "Cannot access file '" << fileName << "'." << endl;
		exit(-1);
	}

	while (EE(xi0, yi0, xi1, yi1) > eta && iteration < 1000){
		xi0 = xi1;
		yi0 = yi1;
		xi1 += psi * dfxydx(xi0, yi0, dx);
		yi1 += psi * dfxydy(xi0, yi0, dy);

		out << xi0 << "\t" << yi0 << "\t>>" << xi1 << "\t" << yi1 << endl;
		iteration++;
	}
	
	out << iteration << "-th E = " << EE(xi0, yi0, xi1, yi1) << endl;
	out << "Maximum Founded: " << fxy(xi1, yi1) << endl;
}