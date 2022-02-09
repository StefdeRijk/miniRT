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
