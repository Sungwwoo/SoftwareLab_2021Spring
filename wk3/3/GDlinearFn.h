#pragma once

class linearFn {
public:
	linearFn();
	linearFn(const char *);
	int N;
	float *x, *y;
	float LossFn(float a, float b);
	float dfabda(float a, float b, float da);
	float dfabdb(float a, float b, float db);
	
//private:
	float SquaredDistance(float, float, float, float);
	//float EE(float, float, float, float);
};