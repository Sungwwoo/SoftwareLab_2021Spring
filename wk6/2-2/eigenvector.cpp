#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>
using namespace Eigen;
using namespace std;

int main()
{
	Matrix2d A, B;
	A << 1, 1, 1, -1;
	B << 3, 0, 0, -1;
	cout << "P * D * P^(-1): " << endl;
	cout << A*B*A.inverse() << endl;

	Matrix2d C, D;
	C << 1, 1, 2, 1;
	D << 2, 0, 0, 3;
	cout << "P * D * P^(-1): " << endl;
	cout << C*D*C.inverse() << endl;
	Matrix2d E, F;
	E << 1, 1, -1, -2;
	F << -1, 0, 0, -2;
	cout << "P * D * P^(-1): " << endl;
	cout << E*F*E.inverse() << endl;


	Matrix3d G, H;
	G << 3, 0, 1, -3, 0, 1, 7, 1, 1;
	H << 3, 0, 0, 0, 6, 0, 0, 0, 7;
	cout << "P * D * P^(-1): " << endl;
	cout << G*H*G.inverse() << endl;
	Matrix3d I, J;
	I << 1, 1, 0, -4, 1, 6, -1, 1, 1;
	J << 2, 0, 0, 0, 9, 0, 0, 0, 2;
	cout << "P * D * P^(-1): " << endl;
	cout << I*J*I.inverse() << endl;
	Matrix3d K, L;
	K << 1./2., 1/sqrt(2), 1./2., -1/sqrt(2), 0, 1/sqrt(2), 1./2., -1/sqrt(2), 1./2.;
	L << 2 - sqrt(2), 0, 0, 0, 2, 0, 0, 0, 2 + sqrt(2);
	cout << "P * D * P^(-1): " << endl;
	cout << K*L*K.inverse() << endl;

	Matrix3d M, N;
	M << 1, 2, 1, -4, 1, 2, 1, 2, -2;
	N << -1, 0, 0, 0, 8, 0, 0, 0, -1;
	cout << "P * D * P^(-1): " << endl;
	cout << M*N*M.inverse() << endl;

	
	return 0;
}