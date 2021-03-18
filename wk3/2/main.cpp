#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>
using namespace std;

#define PI 3.141592

double dx = 0.001, dy = 0.001;

double gaussian(double x, double y, double mux, double muy, double sigx, double sigy, double peak);
double fxy(double x, double y);
double dfxydx(double x, double y, double dx);
double dfxydy(double x, double y, double dy);
double EE(double x0, double y0, double x1, double y1);
void GradientAscent(double xi0, double yi0, double xi1, double yi1, double psi, double eta, int calcs);

int main(){
	int calcs = 1000; // Run 마다 계산할 횟수

	double psi = 0.1, eta = 1e-4;
	cout << "Run 1\n eta: " << eta << ", psi: " << psi << endl << endl;
	// run 1
	cout << "Run 1 - 1" << endl << endl;
	
	double xi1 = -2.5, yi1 = -2.5;
	double xi0 = -3.0, yi0 = -3.0;
	GradientAscent(xi0, yi0, xi1, yi1, psi, eta, calcs);
	cout << "Run 1 - 2" << endl << endl;
	xi1 = 3.0, yi1 = 3.0;
	xi0 = 2.5, yi0 = 2.5;
	GradientAscent(xi0, yi0, xi1, yi1, psi, eta, calcs);

	// run 2
	psi = 0.001, eta = 1e-4;
	cout << "Run 2\n eta: " << eta << ", psi: " << psi << endl << endl;
	cout << "Run 2 - 1" << endl << endl;
	xi1 = -2.5, yi1 = -2.0;
	xi0 = -3.0, yi0 = -3.0;
	GradientAscent(xi0, yi0, xi1, yi1, psi, eta, calcs);
	cout << "Run 2 - 2" << endl << endl;
	xi1 = 3.0, yi1 = 3.0;
	xi0 = 2.5, yi0 = 2.5;
	GradientAscent(xi0, yi0, xi1, yi1, psi, eta, calcs);

	// run 3
	psi = 0.1, eta = 1e-6;
	cout << "Run 3\n eta: " << eta << ", psi: " << psi << endl << endl;
	cout << "Run 3 - 1" << endl << endl;
	xi1 = -2.5, yi1 = -2.5;
	xi0 = -3.0, yi0 = -3.0;
	GradientAscent(xi0, yi0, xi1, yi1, psi, eta, calcs);
	cout << "Run 3 - 2" << endl << endl;
	xi1 = 3.0, yi1 = 3.0;
	xi0 = 2.0, yi0 = 2.0;
	GradientAscent(xi0, yi0, xi1, yi1, psi, eta, calcs);

	// run 4
	psi = 0.001, eta = 1e-6;
	cout << "Run 4\n eta: " << eta << ", psi: " << psi << endl << endl;
	cout << "Run 4 - 1" << endl << endl;
	xi1 = -2.5, yi1 = -2.5;
	xi0 = -3.0, yi0 = -3.0;
	GradientAscent(xi0, yi0, xi1, yi1, psi, eta, calcs);
	cout << "Run 4 - 2" << endl << endl;
	xi1 = 3.0, yi1 = 3.0;
	xi0 = 2.5, yi0 = 2.5;
	GradientAscent(xi0, yi0, xi1, yi1, psi, eta, calcs);

	// run 5
	psi = 0.1, eta = 1e-5;
	cout << "Run 5\n eta: " << eta << ", psi: " << psi << endl << endl;
	cout << "Run 5 - 1" << endl << endl;
	xi1 = -2.5, yi1 = -2.5;
	xi0 = -3.0, yi0 = -3.0;
	GradientAscent(xi0, yi0, xi1, yi1, psi, eta, calcs);
	cout << "Run 5 - 2" << endl << endl;
	xi1 = 3.0, yi1 = 3.0;
	xi0 = 2.5, yi0 = 2.5;
	GradientAscent(xi0, yi0, xi1, yi1, psi, eta, calcs);

	// run 6
	psi = 0.001, eta = 1e-5;
	cout << "Run 6\n eta: " << eta << ", psi: " << psi << endl << endl;
	cout << "Run 6 - 1" << endl << endl;
	xi1 = -2.5, yi1 = -2.5;
	xi0 = -3.0, yi0 = -3.0;
	GradientAscent(xi0, yi0, xi1, yi1, psi, eta, calcs);
	cout << "Run 6 - 2" << endl << endl;
	xi1 = 3.0, yi1 = 3.0;
	xi0 = 2.5, yi0 = 2.5;
	GradientAscent(xi0, yi0, xi1, yi1, psi, eta, calcs);

	return 0;
}

double gaussian(double x, double y, double mux, double muy, double sigx, double sigy, double peak){
	return (peak * exp(-pow((x - mux) / sigx, 2.0) - pow((y - muy) / sigy, 2.0)));
}
double fxy(double x, double y){
	return gaussian(x, y, 1., 1., 1., 2., 4.) + gaussian(x, y, -1., -1., 1., 1., 2.);
}
double dfxydx(double x, double y, double dx){
	return (fxy(x + dx, y) - fxy(x,y)) / dx;
}
double dfxydy(double x, double y, double dy){
	return (fxy(x, y + dy) - fxy(x,y)) / dy;
}
double EE(double x0, double y0, double x1, double y1){
	return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
}

void GradientAscent(double xi0, double yi0, double xi1, double yi1, double psi, double eta, int calcs){
	using namespace std::chrono;

	int iteration = 0;
	int totalIteration = 0;
	int avgIteration = 0;
	double sumx1 = 0, sumy1 = 0;
	double avgx1, avgy1;

	steady_clock::time_point startTime;
	steady_clock::time_point endTime;
	nanoseconds totalTime (0);
	nanoseconds avgTime;

	double x0, y0 , x1, y1;	// Original starting points must stay unchanged

	for (int i = 0; i < calcs; i ++){
		x0 = xi0, y0 = yi1, x1 = xi1, y1 = yi1;
		iteration = 0;
		startTime = steady_clock::now();
		while (EE(x0, y0, x1, y1) > eta && iteration < 10000){
			x0 = x1;
			y0 = y1;
			x1 += psi * dfxydx(x0, y0, dx);
			y1 += psi * dfxydy(x0, y0, dy);
			iteration++;
		}
		sumx1 += x1; 
		sumy1 += y1;
		endTime = steady_clock::now();
		totalTime += duration_cast<nanoseconds> (endTime - startTime);
		totalIteration += iteration;
	}

	avgIteration = totalIteration / calcs;
	avgTime = totalTime / calcs;
	avgx1 = sumx1 / calcs;
	avgy1 = sumy1 / calcs;
	std::cout << "Reached " << setw(10) << avgx1 << setw(10) << avgy1 << std::endl;
	std::cout << "Average Time: " << avgTime.count() << " ns" << std::endl;
	std::cout << "Average Iteration: " << avgIteration<< std::endl;
	std::cout << "E = " << EE(x0, y0, x1, y1) << std::endl;
	std::cout << "Maximum Founded: " << fxy(avgx1, avgy1) << std::endl << std::endl;
}