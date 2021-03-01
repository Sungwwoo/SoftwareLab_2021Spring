#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ofstream out ("Output.txt");

    if (!out){
        cout << "Cannot open file 'Output.txt'." << endl;
        return -1;
    }

    for (int i=1; i<10; i++){
        out << "5 * " << i << " = " << 5 * i << endl;
    }

    return 0;
}