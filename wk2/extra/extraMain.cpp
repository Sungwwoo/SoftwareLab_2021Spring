#include <iostream>
#include "bmpNew.h"
using namespace std;

int main() {
	int x = 0;
	int y = 0;

	
	unsigned char *bmpB = ReadBmp("sunflower.bmp", &x, &y);
	cout << "Resolution: " << x << " by " << y << endl;

	unsigned char *bmpGrayScale = new unsigned char[x * y * 3];
	int grayScale = 0;

	for (int i = 0; i < x * y; i ++){
		grayScale = (0.0722 * bmpB[i * 3] + 0.7152 * bmpB[i * 3 + 1] +  0.2126 * bmpB[i * 3 + 2]);
		bmpGrayScale[i * 3] = grayScale;
		bmpGrayScale[i * 3 + 1] = grayScale;
		bmpGrayScale[i * 3 + 2] = grayScale;
	}

	WriteBmp("GrayScale.bmp", bmpGrayScale, x, y);

	delete[] bmpGrayScale;

	
	unsigned char *bmpYellowToBlue = new unsigned char[x * y * 3];

	for (int i = 0; i < x * y; i ++){
		if ((bmpB[i * 3 + 2] + bmpB[i * 3 + 1]) / 2 > bmpB[i * 3] * 5){
			bmpYellowToBlue[i * 3] = bmpB[i * 3 + 2];				// B
			bmpYellowToBlue[i * 3 + 1] = bmpB[i * 3 + 1];			// G
			bmpYellowToBlue[i * 3 + 2] = bmpB[i * 3];				// R
		}
		else{
			bmpYellowToBlue[i * 3] = bmpB[i * 3];
			bmpYellowToBlue[i * 3 + 1] = bmpB[i * 3 + 1];
			bmpYellowToBlue[i * 3 + 2] = bmpB[i * 3 + 2];
		}
	}

	WriteBmp("blue_sunflower.bmp", bmpYellowToBlue, x, y);

	delete[] bmpB;
	delete[] bmpYellowToBlue;
	
	return 0;
}