#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main(){
    ofstream xx ("Output2.txt");

    if (!xx){
        cout << "Cannot open file 'Output2.txt'." << endl;
        return -1;
    }

    for (int n=0; n<=10; n++){
        xx << n << " " << pow(2, n) << endl;
    }

    return 0;
}