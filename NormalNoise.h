#pragma once
#include <stdlib.h>

class NormalNoise
{
	
private:
	double* noiseMatrix;
	double width;
	double height;
	int rows, cols;
	double gridSize_w, gridSize_h;

	int GenerateNodes();

public:
	static const char INTERPOLATE_SMOOTHSTEP = 0;
	static const char INTERPOLATE_LINEAR = 1;
	static const char INTERPOLATE_PARABOLIC = 2;
	static const char INTERPOLATE_CUBIC = 3;

	///<Summary>
	///	Normal Noise initializing
	///</Summary>
	NormalNoise(int _row, int _col, double _width, double _height);

	int GenerateNoise();

	double GetValue(double x, double y, char InterpolationType);
};

