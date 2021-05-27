#include <fstream>
#include <iostream>
#include <chrono>
#include <random>
using namespace std;

int main(){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(1, 6);

    ofstream output1 ("sprint1.txt");
    int result1[6] = {0, 0, 0, 0, 0, 0};
    int trial = 1e4;

    for (int i = 0; i < trial; i++){
        result1[distribution(generator) - 1]++;
    }
    
    for (int i = 0; i < 6; i++){
        output1 << i + 1 << " " << (double)result1[i] / (double)trial << endl;
    }
    output1.close();

    int n = 10;
    int range = 5 * n + 1;
    trial = 1e5;
    
    ofstream output2 ("sprint2.txt");
    int sum = 0;
    int* result2 = new int[range];

    // Initializing result array
    for (int i = 0; i < range; i++){
        result2[i] = 0;
    }

    for (int i = 0; i < trial; i++){
        sum = 0;
        for (int j = 0; j < n; j++){
            sum += distribution(generator);
        }
        result2[sum-n]++;
    }
    normal_distribution<double> Gauss(n * 3.5, sqrt(n) * 1.71);
    int* result3 = new int[range];
    for (int i = 0; i < range; i++){
        result3[i] = 0;
    }
    int value;
    for (int i = 0; i < trial; i++){
        value = round(Gauss(generator));
        if ((value >= n) && (value <=6 * n)){
            result3[value - n]++;
        }
    }
    
    int sum1 = 0;
    for (int i = 0; i < range; i++){
        output2 << i + n << " " << (double)result2[i] / (double)trial << " " << (double)result3[i] / (double)trial << endl;
        sum1 += result3[i];
    }
    cout << (double)sum1 / (double)trial << endl;
    delete[] result2;
    delete[] result3;

    return 0;
}