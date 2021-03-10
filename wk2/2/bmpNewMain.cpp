#include <iostream>
#include "bmpNew.h"		// Sprint 2
using namespace std;

int main() {
	// Sprint 1
	// Memory allocation 200 * 300 * 3
	int x = 200;
	int y = 300;
	unsigned char *mybmp = new unsigned char[x * y * 3];			
	int r = 0;

	// Creating interlaced datas
	for (int i = 0; i < x * y; i ++){							
		mybmp[i * 3] = 0;
		mybmp[i * 3 + 1] = 0;
		mybmp[i * 3 + 2] = r;
		// Increasing 'red' value from 0 to 255 every row
		if (i % 200 == 0)
			if (r < 255)
				r++;
	}
	
	// Sprint 3
	// Make bmp file
	WriteBmp("mybmp.bmp", mybmp, x, y);						
	delete[] mybmp;

	// Sprint 4
	// Read datas from sunflower.bmp and modify them
	x = 0; y = 0;
	unsigned char *bmpB = ReadBmp("sunflower.bmp", &x, &y);
	unsigned char * bmpBm = new unsigned char[x * y * 3];
	cout << "Resolution: " << x << " by " << y << endl;

	/*
	unsigned char *xxx;
	for (int i = 0; i < x * y * 3; i ++) bmpBm = bmpB[i];
	for (int i = 0; i < 50; i ++){
		xxx = bmpBm + (y - 50 + i) * x * 3 + (x - 100) * 3;
		for (int j = jj = 0; j < 100; j ++, jj += 3){
			xxx[jj] = 0;
			xxx[jj + 1] = 0;
			xxx[jj + 2] = 255;
		}
	}
	*/

	for (int i = 0; i < x * y; i ++){
		if (i % x <= x / 2){
			bmpBm[i * 3] = bmpB[i * 3];
			bmpBm[i * 3 + 1] = bmpB[i * 3 + 1];
			bmpBm[i * 3 + 2] = bmpB[i * 3 + 2];
		}
		else{
			bmpBm[i * 3] = 255 - bmpB[i * 3];
			bmpBm[i * 3 + 1] = 255 - bmpB[i * 3 + 1];
			bmpBm[i * 3 + 2] = 255 - bmpB[i * 3 + 2];
		}
	}

	WriteBmp("modified.bmp", bmpBm, x, y);

	delete[] bmpB;
	delete[] bmpBm;
	
	return 0;
}