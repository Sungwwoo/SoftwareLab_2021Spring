#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/LU>
using namespace Eigen;
using namespace std;
typedef Matrix<float, 6, 6> Matrix6d;
typedef Matrix<float, 6, 1> Vector6d;

int main(){
	Matrix6d A;
	Matrix6d IA;
	Vector6d B, C;

	ifstream inputData("4fit_data_5th.txt");
	if (inputData.fail()){
		cout << "Cannot access '4fit_data_5th.txt'" << endl;
		return -1;
	}
	int N = 100;
	char dummy;
	float *x = new float [N];
	float *y = new float [N];
	for (int i = 0; i < N; i ++)
		inputData >> x[i] >> dummy >> y[i];
	inputData.close();

	float sum_x, sum_x2, sum_x3, sum_x4, sum_x5, sum_x6, sum_x7, sum_x8, sum_x9, sum_x10;
	float sum_y, sum_xy, sum_x2y, sum_x3y, sum_x4y, sum_x5y;
	sum_x = sum_x2 = sum_x3 = sum_x4 = sum_x5 = sum_x6 = sum_x7 = sum_x8 = sum_x9 = sum_x10 = 0;
	sum_y = sum_xy = sum_x2y = sum_x3y = sum_x4y = sum_x5y = 0;

	for (int i = 0; i < N; i++){
		sum_x += x[i];
		sum_x2 += pow(x[i], 2);
		sum_x3 += pow(x[i], 3);
		sum_x4 += pow(x[i], 4);
		sum_x5 += pow(x[i], 5);
		sum_x6 += pow(x[i], 6);
		sum_x7 += pow(x[i], 7);
		sum_x8 += pow(x[i], 8);
		sum_x9 += pow(x[i], 9);
		sum_x10 += pow(x[i], 10);
		sum_y += y[i];
		sum_xy += x[i] * y[i];
		sum_x2y += pow(x[i], 2) * y[i];
		sum_x3y += pow(x[i], 3) * y[i];
		sum_x4y += pow(x[i], 4) * y[i];
		sum_x5y += pow(x[i], 5) * y[i];
	}

	A(0,0) = sum_x5; A(0,1) = sum_x4; A(0,2) = sum_x3; A(0,3) = sum_x2; A(0,4) = sum_x; A(0,5) = N;
	A(1,0) = sum_x6; A(1,1) = sum_x5; A(1,2) = sum_x4; A(1,3) = sum_x3; A(1,4) = sum_x2; A(1,5) = sum_x;
	A(2,0) = sum_x7; A(2,1) = sum_x6; A(2,2) = sum_x5; A(2,3) = sum_x4; A(2,4) = sum_x3; A(2,5) = sum_x2;
	A(3,0) = sum_x8; A(3,1) = sum_x7; A(3,2) = sum_x6; A(3,3) = sum_x5; A(3,4) = sum_x4; A(3,5) = sum_x3;
	A(4,0) = sum_x9; A(4,1) = sum_x8; A(4,2) = sum_x7; A(4,3) = sum_x6; A(4,4) = sum_x5; A(4,5) = sum_x4;
	A(5,0) = sum_x10; A(5,1) = sum_x9; A(5,2) = sum_x8; A(5,3) = sum_x7; A(5,4) = sum_x6; A(5,5) = sum_x5;
	B[0] = sum_y; B[1] = sum_xy; B[2] = sum_x2y; B[3] =sum_x3y, B[4] =sum_x4y, B[5] =sum_x5y;
	IA = A.inverse();
	C = IA * B;

	cout << C << endl;

	ofstream outputData("result.txt");
	outputData << C;
	outputData.close();


	return 0;
}