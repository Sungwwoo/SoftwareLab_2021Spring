#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <random>
using namespace std;

double log_factorial(int n);
double Binomial(int n, int k, double p);
double Poisson(double alpha, int x);

int main(){
    double randmax = (double)RAND_MAX;
    int _mean = 5;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> Uniform(1, 6);

    // Poisson Limit

    // simulation
    int trial = 1e5;
    int count = 0;
    int n = 5;
    double p = 1. / 6.;
    double* sim = new double[n+1];
    double* binomial = new double[n+1];
    double* poisson = new double[n+1];
    for (int k = 0; k <= n; k++){
        sim[k] = 0;
        binomial[k] = 0;
        poisson[k] = 0;
    }
    for (int i = 0; i < trial; i++){
        count = 0;
        for (int k = 0; k <= n; k++){
            if (Uniform(generator) == 6)
                count++;
        }
        sim[count] += 1;
    }
    
    for (int k = 0; k <= n; k++){
        sim[k] /= (double)trial;
    }
    // analytic
    double mean = 0;
    for (int k = 0; k <= n; k++){
        binomial[k] = Binomial(n, k, p);
        poisson[k] = Poisson(n * p, k);
    }
    ofstream output("output.txt");
    output << "k simulation binomial poisson" << endl;
    for (int k = 0; k <= n; k++){
        output << k << " " << sim[k] << " " << binomial[k] << " " << poisson[k] <<endl;
    }
    output.close();

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

double Poisson(double alpha, int x){
    return exp(x * log(alpha) - alpha - log_factorial(x));
}
