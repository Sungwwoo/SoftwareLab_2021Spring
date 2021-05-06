#include <iostream>
#include <cmath>
#include <chrono>
#include <random>
using namespace std;

double log_factorial(int n);
double Binomial(int n, int k, double p);

int main(){
    double randmax = (double)RAND_MAX;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, randmax);
    int n = 10;
    int count;
    int trial = 1e4;
    double p = 1. / 6.; // 패킷 손실될 확률
    double* pk_sim = new double[n + 1];
    double* pk_analytic = new double[n + 1];
    double mean_sim, var_sim, mean_analytic, var_analytic;
    mean_sim = var_sim = mean_analytic = var_analytic = 0;

    // initializing array
    for (int i = 0; i <= n; i++){
        pk_sim[i] = 0;
        pk_analytic[i] = 0;
    }

    // analytic
    for (int k = 0; k <= n; k++){
        pk_analytic[k] = Binomial(n, k, p);
        mean_analytic += k * pk_analytic[k];
        var_analytic += k * k * pk_analytic[k];
    }
    var_analytic -= mean_analytic * mean_analytic;

    // simulation
    for (int i = 0; i < trial; i ++){
        count = 0;
        for (int k = 0; k < n; k++){
            if ((double)distribution(generator) / randmax < p)  // packet lost
                count++;
        }
        pk_sim[count] += 1;
        mean_sim += count;
        var_sim += count * count;
    }

    for (int k = 0; k <= n; k++){
        pk_sim[k] /= (double)trial;
    }
    mean_sim /= (double)trial;
    var_sim = var_sim / (double)trial - mean_sim * mean_sim;
    cout << "\tsim\tanalytic" << endl;
    cout << "mean\t" << mean_sim <<"\t" << mean_analytic << endl;
    cout << "var\t" << var_sim <<"\t" << var_analytic << endl;
    cout << endl;
    for (int k = 0; k <= n; k++){
        cout << k << "\t" << pk_sim[k] << "\t" << pk_analytic[k] << endl;
    }
    return 0;
}

double log_factorial(int n){
    double value = 0;
    for (int i = 1; i <= n; i++)
        value += log(i);
    return value;
}

double Binomial(int n, int k, double p){
    return exp((log_factorial(n) - log_factorial(k) - log_factorial(n - k)) + log(pow(p, k) * pow(1 - p, n - k)));
}
