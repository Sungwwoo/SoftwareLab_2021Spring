#include <iostream>
#include "bmpNew.h"		// Sprint 2
using namespace std;

int main() {
	// Sprint 1
	// Memory allocation 200 * 300 * 3
	int x = 200;
	int y = 300;
	unsigned char *mybmp = new unsigned char[x * y * 3];			
	int red = 0;

	// Creating interlaced datas
	for (int i = 0; i < x * y; i ++){							
		mybmp[i * 3] = 0;
		mybmp[i * 3 + 1] = 0;
		mybmp[i * 3 + 2] = red;
		// Increasing 'red' value from 0 to 255 every row
		if (i % 200 == 0)
			if (red < 255)
				red++;
	}
	
	// Sprint 3
	// Make bmp file
	WriteBmp("mybmp.bmp", mybmp, x, y);						
	delete[] mybmp;

	// Sprint 4
	// Read datas from sunflower.bmp and modify them
	x = 0; y = 0;
	unsigned char *bmpB = ReadBmp("sunflower.bmp", &x, &y);
	unsigned char *bmpBm = new unsigned char[x * y * 3];
	cout << "Resolution: " << x << " by " << y << endl;

	
	
	for (int i = 0; i < x * y; i ++) {
		if ((i % x >= x - 100) && (i / x < 50)){
			bmpBm[i * 3] = 0;
			bmpBm[i * 3 + 1] = 0;
			bmpBm[i * 3 + 2] = 255;
		}
		else{
			bmpBm[i * 3] = bmpB[i * 3];
			bmpBm[i * 3 + 1] = bmpB[i * 3 + 1];
			bmpBm[i * 3 + 2] = bmpB[i * 3 + 2];
		}
	}
	
	WriteBmp("modified.bmp", bmpBm, x, y);

	
	delete[] bmpB;
	delete[] bmpBm;
	
	return 0;
}