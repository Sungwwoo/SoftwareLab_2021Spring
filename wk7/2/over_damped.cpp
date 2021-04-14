#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

float func(float t){		// analytic solution
	return exp(-20 * t) - exp(-5 * t);
}
int main(){
	float dt = 0.01;
	float x2, x0 = 0;			// x2 = x[n+2], x1 = x[n+1], x0 = x[n]
	float x1 = dt * -15 + x0; 	// x1 = dt * x'(0) + x0
	float k = 10;
	const float m = 0.1, b = 2.5;
	cout << x1 << endl;

	ofstream output("over_damped.txt");
	output << 0 << " " << x0 << " " << func(0.0) << endl;
	output << dt << " " << x1 << " " << func(dt) << endl;
	for (float t = 2 * dt; t < 5.0; t += dt){
		x2 = -(-2 + b * dt / m + pow(dt,2) * k / m) * x1 -(1 - b * dt / m) * x0;
		output << t << " " << x2 << " " << func(t) << endl;
		x0 = x1;
		x1 = x2;
	}

	return 0;
}