#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define PI 3.141592

int main(){
	float row[20];
	float t = 0;
	float dx = (2 * PI) / 20;
	for (int i = 0; i < 20; i ++){
		row[i] = sin(i * dx);
	}

	float col[20];
	t = 0;
	float dy = (2 * PI) / 20;
	for (int i = 0; i < 20; i ++){
		col[i] = sin(i * dy);
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
	for (int i = 1; i < 21; i ++){
		out << col[i - 1] << "\t";
		for (int j = 1; j < 21; j ++){
			out << col[i - 1] * row[j - 1] << "\t";
		}
		out << endl;
	}

	return 0;
}