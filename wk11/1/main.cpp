#include <fstream>
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>
using namespace std;
using namespace Eigen;

const int numFeatures = 3; // features (x, y, z)
const int N = 200; // 200 points

class dataX {
public:
	dataX() {
		mean.resize(numFeatures);
		covariance.resize(numFeatures, numFeatures);
	};
	void analyze(VectorXf *data) {
        // initialize mean vector
		for (int p = 0; p < numFeatures; p++) 
            mean[p] = 0.0;

        // calculate mean
		for (int n = 0; n < N; n++) 
            mean += data[n];
		mean /= (float)N;

		// calculate covariance
		for (int j = 0; j < numFeatures; j++) {
			for (int k = 0; k < numFeatures; k++) {
				covariance(j, k) = 0.0;
				for (int n = 0; n < N; n++) {
					covariance(j, k) += (data[n][j] - mean[j]) * (data[n][k] - mean[k]);
				}
				covariance(j, k) /= N - 1;
			}
		}
	}

	VectorXf mean;
	MatrixXf covariance;
};

int main(){
    VectorXf fullData[N];
    ofstream output("covariance.txt");
    if (output.fail())
        return 2;
    dataX data;
    ifstream input("planeCloud200.txt");
    if (input.fail())
        return 3;

    int dumm;
    for (int i = 0; i < N; i++){
        fullData[i].resize(numFeatures);
        for (int j = 0; j < numFeatures; j++)
            input >> fullData[i][j];
    }

    data.analyze(fullData);
    output << "\nMean\n" << data.mean << endl;
    output << "\nCovariance\n" << data.covariance << endl << endl;
    input.close();

    EigenSolver<MatrixXf> es;
    es.compute(data.covariance);
    output << "Eigenvalues of covariance matrix" << endl << es.eigenvalues() << endl << endl;
    MatrixXf P(numFeatures, numFeatures);
	for (int i = 0; i < numFeatures; i++) 
        for (int j = 0; j < numFeatures; j++)
		    P(i, j) = es.eigenvectors()(i, j).real();

	output << "P" << endl << P << endl;
    
    MatrixXf proj2d(3, 2);
    
	for (int i = 0; i < numFeatures; i++){
		proj2d(i, 0) = es.eigenvectors()(i, 0).real();
		proj2d(i, 1) = es.eigenvectors()(i, 2).real();
    }
    cout << proj2d << endl;
	output << "P" << endl << P << endl;

    ofstream dimension2("2d.txt");
    MatrixXf temp2(1, 2);
    MatrixXf temp1(1, 3);
    for (int i = 0; i < N; i++){
        temp1(0,0) = fullData[i][0];
        temp1(0,1) = fullData[i][1];
        temp1(0,2) = fullData[i][2];
        dimension2 << (temp1*proj2d)(0,0) << " " << (temp1*proj2d)(0,1) << endl;
    }
    return 0;
}