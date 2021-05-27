#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/LU>
using namespace std;
using namespace Eigen;

#define M 1e12
#define N 20

const double pi = 3.141592;

class basis
{
public:
    basis(){};
    basis(int n, int type)
    {
        float sqt = sqrt(2.0 / (double)n);
        c = VectorXd(n);
        if (type == 0)
        {
            for (int i = 0; i < n; i++)
            {
                c[i] = sqt * cos(2 * pi * i / n);
            }
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                c[i] = sqt * sin(2 * pi * i / n);
            }
        }
    }

    VectorXd c;
};

int main()
{

    int n = 20;  // wavelet size
    int m = 1e6; // data size
    int sigAmp = 10;
    int n_0 = 0.01 * sigAmp * sigAmp; // noise power
    // random variables
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> Uniform(0, 1);
    normal_distribution<double> Gauss(0, sqrt(n_0 / 2.));

    basis c0, c1;
    c0 = basis(n, 0);
    c1 = basis(n, 1);

    // checking orthonormality
    cout << "c0 c0: " << c0.c.dot(c0.c) << endl;
    cout << "c0 c1: " << c0.c.dot(c1.c) << endl;
    cout << "c1 c1: " << c1.c.dot(c1.c) << endl;

    VectorXd data(m);
    VectorXd *sender = new VectorXd[m / 2];

    // creat data
    for (int i = 0; i < m; i++){
        data[i] = Uniform(generator);
    }

    // encode and send
    double a0, a1;
    for (int i = 0; i < m / 2; i++){
        if (data[2 * i] == 0){
            if (data[2 * i + 1] == 0){  //00
                a0 = 1;
                a1 = 1;
            }
            else{                   //01
                a0 = 1;
                a1 = -1;
            }
        }
        else{
            if (data[2 * i + 1] == 0){  //10
                a0 = -1;
                a1 = 1;
            }
            else{                   //11
                a0 = -1;
                a1 = -1;
            }
        }
        sender[i] = sigAmp * (a0 * c0.c + a1 * c1.c);
    }
    cout << endl;
    ofstream sendedData("sended.txt");
    for (int i = 0; i < m / 2; i++){
        for (int j = 0; j < n; j++){
            sendedData << sender[i][j] << " ";
        }
    }

    // channel
    VectorXd *receiver = new VectorXd[m / 2];

    for (int i = 0; i < m / 2; i++){
        receiver[i] = sender[i];
        for (int j = 0; j < n; j++){
            receiver[i][j] = receiver[i][j] + Gauss(generator);
        }
    }

    // decoder
    VectorXd decoded(m);
    double a0d, a1d;

    ofstream decodedData("decoded.txt");
    for (int i = 0; i < m / 2; i++){
        a0d = receiver[i].dot(c0.c) / sigAmp;
        a1d = receiver[i].dot(c1.c) / sigAmp;
        decodedData << a0d << " " << a1d << " ";
        if (a0d > 0)
            decoded[2 * i] = 0;
        else
            decoded[2 * i] = 1;
            
        if (a1d > 0)
            decoded[2 * i + 1] = 0;
        else
            decoded[2 * i + 1] = 1;
    }
    
    ofstream receivedData("received.txt");
    for (int i = 0; i < m / 2; i++){
        for (int j = 0; j < n; j++){
            receivedData << receiver[i][j] << " ";
        }
    }

    VectorXd error(m);
    for (int i = 0; i < m; i++){
        error[i] = data[i] - decoded[i];
    }
    int cntError = 0;

    for (int i = 0; i < m; i++){
        if (error[i] != 0)
            cntError++;
    }
    double ber = (double)cntError / (double)m;
    
    cout << "BER: " << ber << endl;

    return 0;
}