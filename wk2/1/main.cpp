#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define PI 3.141592

int main(){
	float row[20];
	float col[20];
	float dx = (2 * PI) / 20;
	float dy = (2 * PI) / 20;

	for (int i = 0; i < 20; i ++){
		row[i] = i * dx;
	}
	for (int i = 0; i < 20; i ++){
		col[i] = i * dy;
	}
	
	ofstream out ("output.txt");

	if (!out){
		cout << "Cannot access file 'output.txt'." << endl;
		return -1;
	}
	
	out << "\t";
	for (int i = 0; i < 20; i ++){
		out << row[i] << "\t";
	}

	out << endl;
	for (int i = 0; i < 20; i ++){
		out << col[i] << "\t";
		for (int j = 0; j < 20; j ++){
			out << sin(col[i]) * sin(row[j]) << "\t";
		}
		out << endl;
	}

	return 0;
}