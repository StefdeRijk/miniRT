#include "miniRT.h"

int	trgb_to_int(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

float	tone_mapping(float i)
{
	return (i / (i + 1.));
}

float	color_to_float(int color)
{
	return ((float)color / 255.);
}

int	float_to_color(float color)
{
	return (tone_mapping(color) * 255.);
}
