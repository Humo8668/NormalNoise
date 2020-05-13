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
			NoiseVal = Noise.GetValue(j, i, Noise.INTERPOLATE_SMOOTHSTEP);
			grayShade = (int)((NoiseVal + 1) * 127);
			color = RGB(grayShade, grayShade, grayShade);
			SetPixel(W.hDC, j, i, color);
		}
	}
}





int main()
{
	Window Win(0, 0, 500, 500);

	Win.Show();


	int rows = 50,
		columns = 50;

	double	NoiseWidth = 500.0,
			NoiseHeight = 500.0;
	NormalNoise Noise(rows, columns, NoiseWidth, NoiseHeight);

	Noise.GenerateNoise();

	DrawNoise(Win, Noise, 500, 500);

	Win.StartEventSystem();
	return 0;
}