#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>
#include "bmpNew.h"
using namespace Eigen;
using namespace std;

void AffineTransform(int xp, int yp, float* Ai, int* x, int* y);

int main() {
	int X, Y;
	unsigned char* originalImage = ReadBmp("sunflower.bmp", &X, &Y);

	if (!originalImage) {
		cout << "Cannot access input file." << endl;
		return 2;
	}

	cout << "Resolution: " << X << " * " << Y << endl;

	unsigned char* outputImage = new unsigned char[X * Y * 3];

	Matrix2d A; // 2 by 2 matrix
	A(0, 0) = 1; A(0, 1) = 1;
	A(1, 0) = 1; A(1, 1) = -3;

	Matrix2d B; // 2 by 2 matrix
	B = A.inverse();
	cout << A << endl << B << endl;

	float Ai[4];
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			Ai[i * 2 + j] = B(i, j);
	
	int x, y;
	// Calculate Affine Transform
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

	WriteBmp("TransformedSunflower.bmp", outputImage, X, Y);

	EigenSolver<MatrixXd> es;
	es.compute(A);
	// Eigenvalue: x, y방향으로 어떻게 선형변환되었는지 나타냄
	cout << "EigenValue:	" << endl << es.eigenvalues().real() << endl;
	// Eigenvector: 회전변환 나타냄
	cout << "EigenVector:	" << endl << es.eigenvectors().real() << endl;

	return 0;
}

void AffineTransform(int xp, int yp, float* Ai, int* x, int* y) {
	// Calculates corresponding coordinate
	// xp,	yp	: 원래 좌표
	// x,	y	: 변환된 좌표
	*x = (int)(xp * Ai[0] + yp * Ai[1]);
	*y = (int)(xp * Ai[2] + yp * Ai[3]);
}