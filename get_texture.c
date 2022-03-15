#include "miniRT.h"
#include <math.h>

t_vec3f	get_plane_texture(t_plane plane, t_vec3f plane_pos)
{
	t_plane	texture_plane;
	int		bump_x;
	int		bump_y;
	int		base_index;

	bump_x = ((int)(fabsf(plane_pos.x) * plane.texture.width)) \
		% plane.texture.width;
	bump_y = ((int)(fabsf(plane_pos.y) * plane.texture.height)) \
		% plane.texture.height;
	base_index = bump_x * plane.bump_map.bytes_per_pixel + \
		bump_y * plane.bump_map.bytes_per_row;
	texture_plane = plane;
	texture_plane.color.x = (float)plane.texture.data[base_index] / 255;
	texture_plane.color.y = (float)plane.texture.data[base_index + 1] / 255.;
	texture_plane.color.z = (float)plane.texture.data[base_index + 2] / 255.;
	return (texture_plane.color);
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
	t_sphere	texture_sphere;
	t_vec3f		normal;
	int			base_index;

	normal = get_normal_sphere(at(r, hit.hit_min), sphere.pos);
	base_index = get_sphere_base_index(sphere, normal);
	texture_sphere = sphere;
	texture_sphere.color.x = (float)sphere.texture.data[base_index] / 255.;
	texture_sphere.color.y = (float)sphere.texture.data[base_index + 1] / 255.;
	texture_sphere.color.z = (float)sphere.texture.data[base_index + 2] / 255.;
	if (BONUS && sphere.material == CHECKER)
		return (get_color_checkerboard_sphere(texture_sphere, normal));
	return (texture_sphere.color);
}
