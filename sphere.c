#include "miniRT.h"
#include <math.h>

t_vec3f	get_normal_bump_sphere(t_vec3f hit_point, t_vec3f sphere_center, t_sphere sphere)
{
	t_vec3f	normal;
	int		bump_x;
	int		bump_y;
	float	x_angle;
	float	y_angle;

	normal = get_normal_sphere(hit_point, sphere_center);
	if (!sphere.bump_map.texture_file[0])
		return (normal);
	x_angle = vec3f_dot(vec3f_unit(vec3f_init(normal.x, 0, normal.z)), \
		vec3f_init(1, 0, 0));
	x_angle = acos(x_angle);
	if (normal.z > 0)
		x_angle = x_angle / M_PI;
	else
		x_angle = 2 - x_angle / M_PI;
	x_angle = 2 - x_angle;
	y_angle = vec3f_dot(normal, vec3f_init(0, 1, 0));
	y_angle = acos(y_angle);
	y_angle = 1 - y_angle / M_PI;
	bump_x = ((int)(x_angle / 2.001 * sphere.bump_map.width)) % sphere.bump_map.width;
	bump_y = ((int)(y_angle / 1.001 * sphere.bump_map.height)) % sphere.bump_map.height;
	normal.x += (float)sphere.bump_map.data[bump_x * sphere.bump_map.bytes_per_pixel + bump_y * sphere.bump_map.bytes_per_row] / 128. - 1.;
	normal.y += (float)sphere.bump_map.data[bump_x * sphere.bump_map.bytes_per_pixel + bump_y * sphere.bump_map.bytes_per_row + 1] / 128. - 1.;
	normal.z += (float)sphere.bump_map.data[bump_x * sphere.bump_map.bytes_per_pixel + bump_y * sphere.bump_map.bytes_per_row + 2] / 128. - 1.;
	normal = vec3f_unit(normal);
	return (normal);
}

t_vec3f	get_normal_sphere(t_vec3f hit_point, t_vec3f sphere_center)
{
	return (vec3f_unit(vec3f_sub(hit_point, sphere_center)));
}

t_vec3f	random_in_sphere(void)
{
	t_vec3f	random_point;
	float	x;
	float	y;
	float	z;

	while (1)
	{
		x = (float)rand() / (float)RAND_MAX * 2 - 1;
		y = (float)rand() / (float)RAND_MAX * 2 - 1;
		z = (float)rand() / (float)RAND_MAX * 2 - 1;
		random_point = vec3f_init(x, y, z);
		if (vec3f_len_sq(random_point) <= 1)
			break ;
	}
	return (vec3f_unit(random_point));
}

float	hit_sphere(t_sphere sphere, t_ray r)
{
	float	a;
	float	b;
	float	c;
	float	solution;
	int		solved;

	a = vec3f_len_sq(r.dir);
	b = 2.0 * vec3f_dot(vec3f_sub(r.origin, sphere.pos), r.dir);
	c = vec3f_len_sq(vec3f_sub(r.origin, sphere.pos)) - \
		(sphere.radius * sphere.radius);
	solution = abc(a, b, c, &solved);
	if (!solved)
		return (-1.0);
	return (solution);
}
