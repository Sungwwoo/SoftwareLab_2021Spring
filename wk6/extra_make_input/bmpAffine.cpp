#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>
#include "bmpNew.h"
using namespace Eigen;
using namespace std;
#define PI 3.141592
void AffineTransform(int xp, int yp, float* Ai, int* x, int* y);
void Rotate(unsigned char* outputImage, unsigned char* originalImage, int X, int Y, int theta);
int main() {
	int X, Y;
	unsigned char* originalImage = ReadBmp("softwarelab.bmp", &X, &Y);

	
	if (!originalImage) {
		cout << "Cannot access input file." << endl;
		return 2;
	}

	cout << "Resolution: " << X << " * " << Y << endl;


	unsigned char* outputImage = new unsigned char[X * Y * 3];
	
	int sum, avg, currentWhite;
	int prevWhite = 0;
	int optimalAngle = 0;
	
	
	Rotate(outputImage, originalImage, X, Y, -80);
	WriteBmp("-80.bmp", outputImage, X, Y);

	return 0;
}

void AffineTransform(int xp, int yp, float* Ai, int* x, int* y) {
	// Calculates corresponding coordinate
	// xp,	yp	: 원래 좌표
	// x,	y	: 변환된 좌표
	*x = (int)(xp * Ai[0] + yp * Ai[1]);
	*y = (int)(xp * Ai[2] + yp * Ai[3]);
}

void Rotate(unsigned char* outputImage, unsigned char* originalImage, int X, int Y, int theta){
	float Ai[4];
	int x, y;
	double sinValue, cosValue;
	Matrix2d A, B; // 2 by 2 matrix
	
	sinValue = sin(theta * PI / 180);
	cosValue = cos(theta * PI / 180);

	A(0, 0) = cosValue; A(0, 1) = -sinValue;
	A(1, 0) = sinValue; A(1, 1) = cosValue;
 	B = A.inverse();

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			Ai[i * 2 + j] = B(i, j);

	
	// Calculate Affine Transform
	for (int i = 0; i < X * Y; i ++){
		outputImage[i * 3] = 255;
		outputImage[i * 3 + 1] = 255;
		outputImage[i * 3 + 2] = 255;
	}
	for (int iy = 0; iy < Y; iy++) {
		for (int ix = 0; ix < X; ix++) {
			AffineTransform(ix - X / 2, iy - Y / 2, Ai, &x, &y);
			x += X / 2;
			y += Y / 2;
			if (x < 0 || x >= X || y < 0 || y >= Y)
				continue;
			
			// 변환된 좌표에 원래 좌표의 값 저장
			outputImage[(iy * X + ix) * 3] = originalImage[(y * X + x) * 3];
			outputImage[(iy * X + ix) * 3 + 1] = originalImage[(y * X + x) * 3 + 1];
			outputImage[(iy * X + ix) * 3 + 2] = originalImage[(y * X + x) * 3 + 2];
		}
	}
}