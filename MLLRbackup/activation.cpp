#include "activation.h"
#include <cmath>

	MatrixXd activation::softmax(MatrixXd x, int m, int n) {

		MatrixXd y;
		y.resize(m, n);
		double max = 0.;
		double sum = 0.;

		for (int i = 0; i < x.rows(); i++){
			for (int j = 0; j < x.cols(); j++){
				if (max < x(i,j))
					max = x(i, j);
			}
		}

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++){
				y(i,j) = exp(x(i,j) - max);
				sum += y(i,j);
			}
		}

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++){
				y(i,j) /= sum;
			}
		}

		return y;
	}
