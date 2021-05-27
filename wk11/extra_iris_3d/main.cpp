#include <fstream>
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>
using namespace std;
using namespace Eigen;

const int numFeatures = 4;
const int N = 150;

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
    ofstream output("pca_.txt");
    if (output.fail())
        return 2;
    dataX data;
    ifstream input("iris.txt");
    if (input.fail())
        return 3;

    int* type = new int[N];
    for (int i = 0; i < N; i++){
        fullData[i].resize(numFeatures);
        for (int j = 0; j < numFeatures; j++)
            input >> fullData[i][j];
        input >> type[i];
    }
    data.analyze(fullData);
    output << "\nMean\n" << data.mean << endl;
    output << "\nCovariance\n" << data.covariance << endl << endl;

    EigenSolver<MatrixXf> es;
    es.compute(data.covariance);
    output << "Eigenvalues of covariance matrix" << endl << es.eigenvalues() << endl << endl;
    MatrixXf P(numFeatures, numFeatures);
	for (int i = 0; i < numFeatures; i++) 
        for (int j = 0; j < numFeatures; j++)
		    P(i, j) = es.eigenvectors()(i, j).real();
	output << "P" << endl << P << endl;
    
    
    ofstream dimension2("2d.txt");
    ofstream dimension2_2("2d2.txt");
    ofstream dimension3("3d.txt");
    ofstream dimension3_2("3d2.txt");
    MatrixXf temp1(1, 4);
    MatrixXf proj2d(4, 2);
    MatrixXf proj2d2(4, 2);
    MatrixXf proj3d(4, 3);
    MatrixXf proj3d2(4, 3);
    
	for (int i = 0; i < numFeatures; i++){
		proj3d(i, 0) = es.eigenvectors()(i, 0).real();
		proj3d(i, 1) = es.eigenvectors()(i, 1).real();
		proj3d(i, 2) = es.eigenvectors()(i, 2).real();
        
		proj3d2(i, 0) = es.eigenvectors()(i, 1).real();
		proj3d2(i, 1) = es.eigenvectors()(i, 2).real();
		proj3d2(i, 2) = es.eigenvectors()(i, 3).real();
    }

    
	for (int i = 0; i < numFeatures; i++){
		proj2d(i, 0) = es.eigenvectors()(i, 0).real();
		proj2d(i, 1) = es.eigenvectors()(i, 1).real();
		proj2d2(i, 0) = es.eigenvectors()(i, 2).real();
		proj2d2(i, 1) = es.eigenvectors()(i, 3).real();
    }

    for (int i = 0; i < N; i++){
        temp1(0,0) = fullData[i][0];
        temp1(0,1) = fullData[i][1];
        temp1(0,2) = fullData[i][2];
        temp1(0,3) = fullData[i][3];
        dimension2 << (temp1*proj2d)(0,0) << " " << (temp1*proj2d)(0,1) << " " << type[i] << endl;
        dimension2_2 << (temp1*proj2d2)(0,0) << " " << (temp1*proj2d2)(0,1) << " " << type[i] << endl;
        dimension3 << (temp1*proj3d)(0, 0) << " " <<(temp1*proj3d)(0, 1) << " " <<(temp1*proj3d)(0, 2) << " " << type[i] << endl;
        dimension3_2 << (temp1*proj3d2)(0, 0) << " " <<(temp1*proj3d2)(0, 1) << " " <<(temp1*proj3d2)(0, 2) << " " << type[i] << endl;
    }

    
    return 0;
} 