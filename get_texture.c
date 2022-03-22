#include "miniRT.h"
#include <math.h>

t_vec3f get_texture(t_bmp texture, int base_index)
{
	t_vec3f color;
	color.x = (float)texture.data[base_index] / 255.;
	color.y = (float)texture.data[base_index + 1] / 255.;
	color.z = (float)texture.data[base_index + 2] / 255.;
	return (color);
}

t_vec3f	get_plane_texture(t_plane plane, t_vec3f plane_pos)
{
	t_vec3f color;
	int		bump_x;
	int		bump_y;
	int		base_index;

	bump_x = ((int)(fabsf(plane_pos.x) * plane.texture.width)) \
		% plane.texture.width;
	bump_y = ((int)(fabsf(plane_pos.y) * plane.texture.height)) \
		% plane.texture.height;
	base_index = bump_x * plane.texture.bytes_per_pixel + \
		bump_y * plane.texture.bytes_per_row;
	color = get_texture(plane.texture, base_index);
	return (color);
}

int	get_sphere_base_index(t_sphere sphere, t_vec3f normal)
{
	float		x_angle;
	float		y_angle;
	int			bump_x;
	int			bump_y;
	int			base_index;

	get_sphere_angles(normal, &x_angle, &y_angle);
	bump_x = ((int)(x_angle / 2.001 * sphere.texture.width)) \
		% sphere.texture.width;
	bump_y = ((int)(y_angle / 1.001 * sphere.texture.height)) \
		% sphere.texture.height;
	base_index = bump_x * sphere.texture.bytes_per_pixel + \
		bump_y * sphere.texture.bytes_per_row;
	return (base_index);
}

t_vec3f	get_sphere_texture(t_sphere sphere, t_ray r, t_hits hit)
{
	t_vec3f		texture_color;
	t_vec3f		normal;
	int			base_index;

	normal = get_normal_sphere(at(r, hit.hit_min), sphere.pos);
	base_index = get_sphere_base_index(sphere, normal);
	texture_color = get_texture(sphere.texture, base_index);
	if (BONUS && sphere.material == CHECKER)
		return (get_color_checkerboard_sphere(normal, texture_color));
	return (texture_color);
}
