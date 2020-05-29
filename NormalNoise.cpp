#include "NormalNoise.h"
#include <time.h>
#include <random>
#include <math.h>

const double M_PI = 3.141592653589793238;

double Clamp(double val, double left, double right)
{
	if (val > right)
		return right;
	else if (val < left)
		return left;
	else
		return val;
}

double Max(double a, double b)
{
	return (a > b) ? a : b;
}

double Min(double a, double b)
{
	return (a > b) ? b : a;
}

double GetRandom(double mu, double sigma)
{
	std::random_device mch;
	std::default_random_engine generator(mch());
	std::normal_distribution<double> distr(mu, sigma);

	return distr(generator);
}


NormalNoise::NormalNoise(int nodes_rows, int nodes_cols, double width, double height)
{
	this->rows = nodes_rows;
	this->cols = nodes_cols;
	this->width = width;
	this->height = height;
	this->gridSize_w = width / (cols - 1.0);
	this->gridSize_h = height / (rows - 1.0);
	noiseMatrix = (double*)malloc(nodes_rows * nodes_cols * sizeof(double));
}


int NormalNoise::GenerateNodes()
{
	std::random_device mch;
	std::default_random_engine generator(mch());
	std::normal_distribution<double> NormalDistr(0.0, 0.5);	// sigma = 0.5 for 95% probability that randomizer will generate number in [-1,1]

	for (int i = 0; i < rows; i++)
	{
		noiseMatrix[i * cols + 0] = Clamp(NormalDistr(generator), -1, 1);
	}

	for (int j = 0; j < cols; j++)
	{
		noiseMatrix[0 + j] = Clamp(NormalDistr(generator), -1, 1);
	}

	double sigma, mu;
	for (int i = 1; i < rows; i++)
	{
		for (int j = 1; j < cols; j++)
		{
			//noiseMatrix[i * cols + j] = Clamp(NormalDistr(generator), -1, 1);
			mu = (noiseMatrix[(i - 1) * cols + j] + noiseMatrix[i * cols + j - 1]) / 2.0;	// average
			//sigma = (Max(noiseMatrix[(i - 1) * cols + j], noiseMatrix[i * cols + j - 1]) - mu) / 2.0;	//	95% in [<lowest neighbout point>, <highest neighbour point>]
			noiseMatrix[i * cols + j] = Clamp(GetRandom(mu, 0.5), -1, 1);
		}
	}

	return 0;
}

double NormalNoise::SmoothStep(double t, char FunctionType)
{
	switch (FunctionType)
	{
	case INTERPOLATE_SINUSOID:
		if (t < 0)
			return 0.0;
		else if (t > 1.0)
			return 1.0;
		else
		{
			double sine = sin(t*(M_PI/2));
			return sine * sine;
		}
	
	case INTERPOLATE_LINEAR:
		if (t < 0)
			return 0.0;
		else if (t > 1.0)
			return 1.0;
		else
			return t;
	
	case INTERPOLATE_CUBIC:
		if (t < 0)
			return 0.0;
		else if (t > 1.0)
			return 1.0;
		else
			return 3*t*t - 2*t*t*t;


	default:
		if (t < 0)
			return 0.0;
		else if (t > 1.0)
			return 1.0;
		else
			return t;
	}
	
	return t;
}

double NormalNoise::Interpolate(double left, double right, double t, char InterpolationType)
{
	return left + (right - left) * SmoothStep(t, InterpolationType);
}

double NormalNoise::GetValue(double x, double y, char InterpolationType)
{
	if (x > width || x < 0 ||
		y > height || y < 0)
		return 0.0;

	int row_, col_;
	col_ = (int)floor(x / this->gridSize_w);
	row_ = (int)floor(y / this->gridSize_h);

	double
		x0 = col_ * this->gridSize_w,
		y0 = row_ * this->gridSize_h;

	double x_int_0 = Interpolate
	(
		noiseMatrix[row_ * cols + col_],
		noiseMatrix[row_ * cols + col_+1],
		(x - x0) / gridSize_w, 
		InterpolationType
	);
	
	double x_int_1 = Interpolate
	(
		noiseMatrix[(row_ + 1) * cols + col_], 
		noiseMatrix[(row_ + 1) * cols + col_+1],
		(x - x0) / gridSize_w,
		InterpolationType
	);
	
	double val = Interpolate
	(
		x_int_0,
		x_int_1,
		(y - y0) / gridSize_h, 
		InterpolationType
	);

	return val;
}


int NormalNoise::GenerateNoise()
{
	int errCode = 0;
	errCode = this->GenerateNodes();

	/*for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			printf("%.1lf ", this->noiseMatrix[i * cols + j]);
		}

		printf("\n");
	}*/
	return errCode;
}