#include <iostream>
#include "bmpNew.h"
using namespace std;

int main() {
	// Sprint 1
	unsigned char *mybmp = new unsigned char[180000];
	int r = 0;
	for (int i = 0; i < 60000; i ++){
		if (i % 200 == 0)
			if (r < 255)
			r++;
		mybmp[i * 3] = 0;
		mybmp[i * 3 + 1] = 0;
		mybmp[i * 3 + 2] = r;
	}
	
	WriteBmp("mybmp.bmp", mybmp, 200, 300);
	
	int x, y;
	unsigned char *bmpB = ReadBmp("sunflower.bmp", &x, &y);
	cout << "Main " << x << " by " << y << endl;
	
	return 0;
}