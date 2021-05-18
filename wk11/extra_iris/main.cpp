#include <fstream>
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>
using namespace std;
using namespace Eigen;

const int numFeatures = 4;
const int N = 50;

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
    ofstream output("pca.txt");
    if (output.fail())
        return 2;
    dataX data;
    ifstream input("iris.txt");
    if (input.fail())
        return 3;

    int dummy;
    for (int type = 0; type < 3; type++){
        for (int i = 0; i < N; i++){
            fullData[i].resize(numFeatures);
            for (int j = 0; j < numFeatures; j++)
                input >> fullData[i][j];
            input >> dummy;
        }
        data.analyze(fullData);
        output << "Type\n" << dummy << endl;
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
    }

    input.close();
    output.close();
    return 0;
} 