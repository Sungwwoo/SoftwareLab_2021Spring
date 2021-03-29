#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/LU>
using namespace Eigen;

int main(){
	Matrix2d A;
	Matrix2d IA;
	Vector2d B, C;

	std::ifstream inputData("datae.txt");
	if (inputData.fail()){
		std::cout << "Cannot access 'datae.txt'" << std::endl;
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

	std::cout << sum_x << std::endl;
	std::cout << sum_x2 << std::endl;
	std::cout << sum_lny << std::endl;
	std::cout << sum_xlny << std::endl;
	A(0,0) = sum_x; A(0,1) = count;
	A(1,0) = sum_x2; A(1,1) = sum_x;
	B[0] = sum_lny; B[1] = sum_xlny;
	IA = A.inverse();
	C = IA * B;
	std::ofstream outputData("datae_result.txt");
	C[1] = exp(C[1]);
	for (int i = 0; i < 2; i++){
		outputData << C[i] << " ";
	}
	outputData.close();

	return 0;
}