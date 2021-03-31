#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/LU>
using namespace Eigen;
using namespace std;
int main(){
	Matrix2d A;
	Matrix2d IA;
	Vector2d B, C;

	ifstream inputData("datae.txt");
	if (inputData.fail()){
		cout << "Cannot access 'datae.txt'" << endl;
		return -1;
	}
	int N;
	inputData >> N;
	float *x = new float [N];
	float *y = new float [N];
	for (int i = 0; i < N; i ++)
		inputData >> x[i] >> y[i];
	inputData.close();
	
	float sum_x, sum_x2, sum_lny, sum_xlny;
	sum_x = sum_x2 = sum_lny = sum_xlny = 0;
	int count = 0;
	for (int i = 0; i < N; i++){
		if (y[i] < 0)
			continue;
		else{ 
			sum_x += x[i];
			sum_x2 += x[i] * x[i];
			sum_lny += (float)log(y[i]);
			sum_xlny += x[i] * (float)log(y[i]);
			count ++;
		}
	}

	A(0,0) = sum_x; A(0,1) = count;
	A(1,0) = sum_x2; A(1,1) = sum_x;
	B[0] = sum_lny; B[1] = sum_xlny;
	IA = A.inverse();
	C = IA * B;
	ofstream outputData("datae_result.txt");
	cout << C << endl;
	C[1] = exp(C[1]);
	outputData << C;
	outputData.close();

	return 0;
}