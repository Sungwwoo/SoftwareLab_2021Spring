#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

float func(float t){		// analytic solution
	return exp(-t)*(cos(3*sqrt(11)*t) - (sqrt(11)*sin(3*sqrt(11)*t))/33);
}
int main(){
	float dt = 0.01;
	float x2, x0 = 1;		// x2 = x[n+2], x1 = x[n+1], x0 = x[n]
	float x1 = dt * 0 + x0; // x1 = dt * x'(0) + x0
	float k = 10;
	const float m = 0.1, b = 0.2;

	ofstream output("under_damped.txt");

	if (output.fail()){
		cout << "Cannot access output file." << endl;
		return 2;
	}
	
	output << "t" << "\t" << "Analytic Solution" << "\t" << "Numeric solution" << endl;
	output << 0 << "\t" << x0 << "\t" << func(0.0) << endl;
	output << dt << "\t" << x1 << "\t" << func(dt) << endl;
	for (float t = 2 * dt; t < 5.0; t += dt){
		x2 = -(-2 + b * dt / m + pow(dt,2) * k / m) * x1 -(1 - b * dt / m) * x0;
		output << t << "\t" << x2 << "\t" << func(t) << endl;
		x0 = x1;
		x1 = x2;
	}

	return 0;
}