#include <cmath>
#include <Eigen/Dense>
#include <Eigen/LU>
#include <random>
#define N 20    // dimension of basis vector
#define M 8     // number of data bits
#define A 10.0  // signal amplitude(radius)
using namespace Eigen;
using namespace std;

int main()
{
	default_random_engine generator;
	normal_distribution<double> myGauss(0.0, A); // noise power 

	// make 2 basis vectors
	VectorXd c0(N), c1(N);
	float sqt = sqrt(2.0 / (double)N);
	float piN = 2.*3.141592 / N;
	for (int i = 0; i < N; i++) {
			c0(i) = sqt * cos(piN * i);
			c1(i) = sqt * sin(piN * i);
	}
	//////  sender /////
	VectorXd data = VectorXd(M);  // M bits
	data << 0, 1, 1, 1, 1, 0, 0, 0;
	// M/2 symbols QPSK
	VectorXd* s = new VectorXd[M / 2];  
	float a0, a1;
	for (int i = 0; i < M / 2; i++) {
		if (data[2 * i] == 0) {
			if (data[2 * i + 1] == 0) { 
                a0 = A; a1 = A; 
            }
			else { 
                a0 = 10; a1 = -10; 
            }
		}
		else {
			if (data[2 * i + 1] == 0) { 
                a0 = -A; a1 = A; 
            }
			else { 
                a0 = -A; a1 = -A; 
            }
		}
		s[i] = a0 * c0 + a1 * c1;
	}
	///// channel /////
	VectorXd* r = new VectorXd[M / 2];
	for (int i = 0; i < M / 2; i++) {
		for (int j = 0; j < N; j++) 
            r[i][j] = s[i][j] + myGauss(generator);
	}
	///// receiver /////
	float a0d, a1d;
	for (int i = 0; i < M / 2; i++) {
		a0d = c0.dot(r[i]);
		a1d = c1.dot(r[i]);
	}
}

