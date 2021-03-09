#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define PI 3.141592

int main(){
	float **table = new float* [20];
	for (int i = 0; i < 20; i ++){
		table[i] = new float [20];
	}
	
	
	ofstream out ("output2.txt");

	if (!out){
		cout << "Cannot access file 'output.txt'." << endl;
		return -1;
	}
	

	for (int i = 0; i < 20; i ++){
		delete[] table[i];
	}

	delete[] table;
	
	return 0;
}