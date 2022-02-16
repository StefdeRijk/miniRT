#include "miniRT.h"
#include "vec/vec.h"

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

t_vec3f	color_to_float_vec(t_vec3i color)
{
	t_vec3f	ret;

	ret.x = color_to_float(color.x);
	ret.y = color_to_float(color.y);
	ret.z = color_to_float(color.z);
	return (ret);
}

t_vec3i	float_to_color_vec(t_vec3f color)
{
	t_vec3i	ret;

	ret.x = float_to_color(color.x);
	ret.y = float_to_color(color.y);
	ret.z = float_to_color(color.z);
	return (ret);
}

int	ray_to_pixel_color(t_vec3f ray_colour)
{
	t_vec3i	color_int;
	int		color;

	color_int = float_to_color_vec(ray_colour);
	color = rgb_to_color(color_int);
	return (color);
}
