#include <stdlib.h>
#include <stdio.h>
#include "Window.h"
#include "NormalNoise.h"

void DrawNoise(Window W, NormalNoise Noise, int width, int height)
{
	W.ClearWindow();

	COLORREF color;
	double NoiseVal;
	int grayShade;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			NoiseVal = Noise.GetValue(j, i, Noise.INTERPOLATE_SINUSOID);
			grayShade = (int)((NoiseVal + 1) * 127);
			color = RGB(grayShade, grayShade, grayShade);
			SetPixel(W.hDC, j, i, color);
		}
	}
}





int main()
{
	int	rows = 11,
		columns = 11;

	double	NoiseWidth = 700.0,
			NoiseHeight = 700.0;


	Window Win(0, 0, (int)NoiseWidth, (int)NoiseHeight);
	Win.Show();

	NormalNoise Noise(rows, columns, NoiseWidth, NoiseHeight);
	Noise.GenerateNoise();

	DrawNoise(Win, Noise, (int)NoiseWidth, (int)NoiseHeight);

	Win.StartEventSystem();
	return 0;
}