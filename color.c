#include "vec/vec.h"

int	trgb_to_int(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	rgb_to_color(t_vec3i color)
{
	return (trgb_to_int(0, color.r, color.g, color.b));
}

t_vec3i	color_to_rgb(int color)
{
	t_vec3i	rgb;

	rgb.r = (color & (0xFF << 16)) >> 16;
	rgb.g = (color & (0xFF << 8)) >> 8;
	rgb.b = color & 0xFF;
	return (rgb);
}

float	color_to_float(int color)
{
	return ((float)color / 255.);
}

t_vec3f	color_to_float_vec(t_vec3i color)
{
	t_vec3f	ret;

	ret.x = color_to_float(color.x);
	ret.y = color_to_float(color.y);
	ret.z = color_to_float(color.z);
	return (ret);
}

float	tone_mapping(float i)
{
	return (i / (i + 1.));
}

int	float_to_color(float color)
{
	return (tone_mapping(color) * 255.);
}

t_vec3i	float_to_color_vec(t_vec3f color)
{
	t_vec3i	ret;

	ret.x = float_to_color(color.x);
	ret.y = float_to_color(color.y);
	ret.z = float_to_color(color.z);
	return (ret);
}
