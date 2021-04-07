#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>
using namespace Eigen;
using namespace std;

void Calculate2d(Matrix2d& matrix);
void Calculate3d(Matrix3d& matrix);

int main()
{
	Matrix2d A;
	A << 1, 2, 2, 1;
	Calculate2d(A);
	Matrix2d B;
	B << 4, -1, 2, 1;
	Calculate2d(B);
	Matrix2d C;
	C << 0, 1, -2, -3;
	Calculate2d(C);
	Matrix3d D;
	D << 5, 2, 0, 2, 5, 0, -3, 4, 6;
	Calculate3d(D);
	Matrix3d E;
	E << 4, -1, 6, 2, 1, 6, 2, -1, 8;
	Calculate3d(E);
	Matrix3d F;
	F << 2, 1, 0, 1, 2, 1, 0, 1, 2;
	Calculate3d(F);
	Matrix3d G;
	G << 3, 2, 4, 2, 0, 2, 4, 2, 3;
	Calculate3d(G);
	
	return 0;
}

void Calculate2d(Matrix2d& matrix){
	cout << "--------------------------------------" << endl;
	cout << "Matrix: " << endl << matrix << endl << endl;
	EigenSolver<MatrixXd> es;
	Matrix2d P, D;
	es.compute(matrix);
	cout << "EigenValues: " << endl << es.eigenvalues().real() << endl << endl;
	cout << "EigenVectors: " << endl << es.eigenvectors().real() << endl << endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			P(i,j) = es.eigenvectors()(i, j).real();
			D(i, j) = 0;
		}
		D(i, i) = es.eigenvalues()[i].real();
	}
	cout << "Matrix P: " << endl << P << endl << endl;
	cout << "Matrix D: " << endl << D << endl << endl;
	cout << "Inverse of P:" << endl << P.inverse() << endl << endl;
	if (matrix == matrix.transpose()){	// 전치행렬일 경우 P == P^T 확인
		cout << "Transpose of P:" << endl << P.transpose() << endl << endl;
	}
	cout << "P * D * P^(-1): " << endl << P*D*P.inverse() << endl;
	cout << "--------------------------------------" << endl;
}

void Calculate3d(Matrix3d& matrix){
	cout << "--------------------------------------" << endl;
	cout << "Matrix: " << endl << matrix << endl << endl;
	EigenSolver<MatrixXd> es;
	Matrix3d P, D;
	es.compute(matrix);
	cout << "EigenValues: " << endl << es.eigenvalues().real() << endl << endl;
	cout << "EigenVectors: " << endl << es.eigenvectors().real() << endl << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			P(i,j) = es.eigenvectors()(i, j).real();
			D(i, j) = 0;
		}
		D(i, i) = es.eigenvalues()[i].real();
	}
	cout << "Matrix P: " << endl << P << endl << endl;
	cout << "Matrix D: " << endl << D << endl << endl;
	cout << "Inverse of P:" << endl << P.inverse() << endl << endl;
	if (matrix == matrix.transpose()){	// 전치행렬일 경우 P == P^T 확인
		cout << "Transpose of P:" << endl << P.transpose() << endl << endl;
	}
	cout << "P * D * P^(-1): " <<endl << P*D*P.inverse() << endl;
	cout << "--------------------------------------" << endl;
}