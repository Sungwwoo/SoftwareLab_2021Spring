#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <Eigen/LU>
using namespace Eigen;
using namespace std;

int main(){
	Matrix3d A;
	Matrix3d IA;
	Vector3d B, C;

	ifstream inputData("data2.txt");
	if (inputData.fail()){
		cout << "Cannot access 'data.txt'" << endl;
		return -1;
	}
	int N;
	inputData >> N;
	float *x = new float [N];
	float *y = new float [N];
	for (int i = 0; i < N; i ++)
		inputData >> x[i] >> y[i];
	inputData.close();

	float sum_x, sum_x2, sum_x3, sum_x4, sum_y, sum_xy, sum_x2y;
	sum_x = sum_x2 = sum_x3 = sum_x4 = sum_y = sum_xy = sum_x2y = 0;
	for (int i = 0; i < N; i++){
		sum_x += x[i];
		sum_x2 += x[i] * x[i];
		sum_x3 += x[i] * x[i] * x[i];
		sum_x4 += x[i] * x[i] * x[i] * x[i];
		sum_y += y[i];
		sum_xy += x[i] * y[i];
		sum_x2y += x[i] * x[i] * y[i];
	}

	A(0,0) = sum_x2; A(0,1) = sum_x; A(0,2) = N;
	A(1,0) = sum_x3; A(1,1) = sum_x2; A(1,2) = sum_x;
	A(2,0) = sum_x4; A(2,1) = sum_x3; A(2,2) = sum_x2;
	B[0] = sum_y; B[1] = sum_xy; B[2] = sum_x2y;
	IA = A.inverse();
	C = IA * B;

	cout << C << endl;

	ofstream outputData("data2result.txt");
	outputData << C;
	outputData.close();

	return 0;
}