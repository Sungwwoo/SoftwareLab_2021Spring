#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <random>
using namespace std;

#define PI 3.141592

double dx = 0.001, dy = 0.001, dz = 0.001;

double fxyz(double x, double y, double z);
double dfxyzdx(double x, double y, double z, double dx);
double dfxyzdy(double x, double y, double z, double dy);
double dfxyzdz(double x, double y, double z, double dz);
double EE(double x0, double y0, double z0, double x1, double y1, double z1);
void GradientAscent(double xi0, double yi0, double zi0, double xi1, double yi1, double zi1, double psi, double eta, int calcs);
void GradientDescent(double xi0, double yi0, double zi0, double xi1, double yi1, double zi1, double psi, double eta, int calcs);

int main(){
	int calcs = 1000; // Run 마다 계산할 횟수

	// Random Number Generator
	default_random_engine generator;
	uniform_real_distribution<double> distribution(0.0, 1.0);

	double psi = 1e-3, eta = 1e-6;
	double xi1, yi1, zi1;
	double xi0, yi0, zi0;
	
	xi1 = distribution(generator), yi1 = distribution(generator), zi1 = distribution(generator);
	xi0 = distribution(generator), yi0 = distribution(generator), zi0 = distribution(generator);
	cout << "Initial Point:" << setw(12) << xi0 << setw(12) << yi0 << setw(12) << zi0 << "," << setw(12) << xi1 << setw(12) << yi1 << setw(12) << zi1 << endl;
	GradientAscent(xi0, yi0, zi0, xi1, yi1, zi1, psi, eta, calcs);
	xi1 = distribution(generator), yi1 = distribution(generator), zi1 = distribution(generator);
	xi0 = distribution(generator), yi0 = distribution(generator), zi0 = distribution(generator);
	cout << "Initial Point:" << setw(12) << xi0 << setw(12) << yi0 << setw(12) << zi0 << ","  << setw(12) << xi1 << setw(12) << yi1 << setw(12) << zi1 << endl;
	GradientAscent(xi0, yi0, zi0, xi1, yi1, zi1, psi, eta, calcs);
	xi1 = distribution(generator), yi1 = distribution(generator), zi1 = distribution(generator);
	xi0 = distribution(generator), yi0 = distribution(generator), zi0 = distribution(generator);
	cout << "Initial Point:" << setw(12) << xi0 << setw(12) << yi0 << setw(12) << zi0 << ","  << setw(12) << xi1 << setw(12) << yi1 << setw(12) << zi1 << endl;
	GradientAscent(xi0, yi0, zi0, xi1, yi1, zi1, psi, eta, calcs);
	xi1 = distribution(generator), yi1 = distribution(generator), zi1 = distribution(generator);
	xi0 = distribution(generator), yi0 = distribution(generator), zi0 = distribution(generator);
	cout << "Initial Point:" << setw(12) << xi0 << setw(12) << yi0 << setw(12) << zi0 << ","  << setw(12) << xi1 << setw(12) << yi1 << setw(12) << zi1 << endl;
	GradientAscent(xi0, yi0, zi0, xi1, yi1, zi1, psi, eta, calcs);

	xi1 = distribution(generator), yi1 = distribution(generator), zi1 = distribution(generator);
	xi0 = distribution(generator), yi0 = distribution(generator), zi0 = distribution(generator);
	cout << "Initial Point:" << setw(12) << xi0 << setw(12) << yi0 << setw(12) << zi0 << ","  << setw(12) << xi1 << setw(12) << yi1 << setw(12) << zi1 << endl;
	GradientDescent(xi0, yi0, zi0, xi1, yi1, zi1, psi, eta, calcs);
	xi1 = distribution(generator), yi1 = distribution(generator), zi1 = distribution(generator);
	xi0 = distribution(generator), yi0 = distribution(generator), zi0 = distribution(generator);
	cout << "Initial Point:" << setw(12) << xi0 << setw(12) << yi0 << setw(12) << zi0 << ","  << setw(12) << xi1 << setw(12) << yi1 << setw(12) << zi1 << endl;
	GradientDescent(xi0, yi0, zi0, xi1, yi1, zi1, psi, eta, calcs);
	xi1 = distribution(generator), yi1 = distribution(generator), zi1 = distribution(generator);
	xi0 = distribution(generator), yi0 = distribution(generator), zi0 = distribution(generator);
	cout << "Initial Point:" << setw(12) << xi0 << setw(12) << yi0 << setw(12) << zi0 << ","  << setw(12) << xi1 << setw(12) << yi1 << setw(12) << zi1 << endl;
	GradientDescent(xi0, yi0, zi0, xi1, yi1, zi1, psi, eta, calcs);
	xi1 = distribution(generator), yi1 = distribution(generator), zi1 = distribution(generator);
	xi0 = distribution(generator), yi0 = distribution(generator), zi0 = distribution(generator);
	cout << "Initial Point:" << setw(12) << xi0 << setw(12) << yi0 << setw(12) << zi0 << ","  << setw(12) << xi1 << setw(12) << yi1 << setw(12) << zi1 << endl;
	GradientDescent(xi0, yi0, zi0, xi1, yi1, zi1, psi, eta, calcs);

	return 0;
}


double fxyz(double x, double y, double z){
	return sin(2 * PI * x) * sin(4 * PI * y) * sin(8 * PI * z);
}
double dfxyzdx(double x, double y, double z, double dx){
	return (fxyz(x + dx, y, z) - fxyz(x,y,z)) / dx;
}
double dfxyzdy(double x, double y, double z, double dy){
	return (fxyz(x, y + dy, z) - fxyz(x,y,z)) / dy;
}

double dfxyzdz(double x, double y, double z, double dz){
	return (fxyz(x, y, z + dz) - fxyz(x,y,z)) / dz;
}

double EE(double x0, double y0, double z0, double x1, double y1, double z1){
	return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1) + (z0 - z1) * (z0 - z1));
}

void GradientAscent(double xi0, double yi0, double zi0, double xi1, double yi1, double zi1, double psi, double eta, int calcs){
	using namespace std::chrono;

	int iteration = 0;
	int totalIteration = 0;
	int avgIteration = 0;
	double sumx1 = 0, sumy1 = 0, sumz1 = 0;
	double avgx1, avgy1, avgz1;

	steady_clock::time_point startTime;
	steady_clock::time_point endTime;
	nanoseconds totalTime (0);
	nanoseconds avgTime;

	double x0, y0, z0, x1, y1, z1;	// Original starting points must stay unchanged

	for (int i = 0; i < calcs; i ++){
		x0 = xi0, y0 = yi1, z0 = zi0, x1 = xi1, y1 = yi1, z1 = zi1;
		iteration = 0;
		startTime = steady_clock::now();
		while (EE(x0, y0, z0, x1, y1, z1) > eta && iteration < 1e7){
			x0 = x1;
			y0 = y1;
			z0 = z1;
			x1 += psi * dfxyzdx(x0, y0, z0, dx);
			y1 += psi * dfxyzdy(x0, y0, z1, dy);
			z1 += psi * dfxyzdz(x0, y0, z1, dz);
			iteration++;
		}
		sumx1 += x1; 
		sumy1 += y1;
		sumz1 += z1;
		endTime = steady_clock::now();
		totalTime += duration_cast<nanoseconds> (endTime - startTime);
		totalIteration += iteration;
	}

	avgIteration = totalIteration / calcs;
	avgTime = totalTime / calcs;
	avgx1 = sumx1 / calcs;
	avgy1 = sumy1 / calcs;
	avgz1 = sumz1 / calcs;
	std::cout << "Reached " << setw(12) << avgx1 << setw(12) << avgy1 << setw(12) << avgz1 << std::endl;
	std::cout << "Average Time: " << avgTime.count() << " ns" << std::endl;
	std::cout << "Average Iteration: " << avgIteration<< std::endl;
	std::cout << "E = " << EE(x0, y0, z0, x1, y1, z1) << std::endl;
	std::cout << "Maximum Founded: " << fxyz(avgx1, avgy1, avgz1) << std::endl << std::endl;
}

void GradientDescent(double xi0, double yi0, double zi0, double xi1, double yi1, double zi1, double psi, double eta, int calcs){
	using namespace std::chrono;

	int iteration = 0;
	int totalIteration = 0;
	int avgIteration = 0;
	double sumx1 = 0, sumy1 = 0, sumz1 = 0;
	double avgx1, avgy1, avgz1;

	steady_clock::time_point startTime;
	steady_clock::time_point endTime;
	nanoseconds totalTime (0);
	nanoseconds avgTime;

	double x0, y0, z0, x1, y1, z1;	// Original starting points must stay unchanged

	for (int i = 0; i < calcs; i ++){
		x0 = xi0, y0 = yi1, z0 = zi0, x1 = xi1, y1 = yi1, z1 = zi1;
		iteration = 0;
		startTime = steady_clock::now();
		while (EE(x0, y0, z0, x1, y1, z1) > eta && iteration < 1e7){
			x0 = x1;
			y0 = y1;
			z0 = z1;
			x1 -= psi * dfxyzdx(x0, y0, z0, dx);
			y1 -= psi * dfxyzdy(x0, y0, z1, dy);
			z1 -= psi * dfxyzdz(x0, y0, z1, dz);
			iteration++;
		}
		sumx1 += x1; 
		sumy1 += y1;
		sumz1 += z1;
		endTime = steady_clock::now();
		totalTime += duration_cast<nanoseconds> (endTime - startTime);
		totalIteration += iteration;
	}

	avgIteration = totalIteration / calcs;
	avgTime = totalTime / calcs;
	avgx1 = sumx1 / calcs;
	avgy1 = sumy1 / calcs;
	avgz1 = sumz1 / calcs;
	std::cout << "Reached " << setw(12) << avgx1 << setw(12) << avgy1 << setw(12) << avgz1 << std::endl;
	std::cout << "Average Time: " << avgTime.count() << " ns" << std::endl;
	std::cout << "Average Iteration: " << avgIteration<< std::endl;
	std::cout << "E = " << EE(x0, y0, z0, x1, y1, z1) << std::endl;
	std::cout << "Minimum Founded: " << fxyz(avgx1, avgy1, avgz1) << std::endl << std::endl;
}