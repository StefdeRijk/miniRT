#include "miniRT.h"
#include <math.h>

t_vec3f	get_normal_bump_sphere(t_vec3f hit_point, t_vec3f sphere_center, t_sphere sphere)
{
	t_vec3f	normal;
		
	normal = vec3f_unit(vec3f_sub(hit_point, sphere_center));
	if (!sphere.bump_map.texture_file[0])
		return (normal);
	bump_x = ((int)(fabsf(angle_on_sphere.x) / (2.001 * M_PI) * plane.bump_map.width));
	bump_y = ((int)((angle_on_sphere.y + (M_PI / 2.)) / (1.001 * M_PI) * plane.bump_map.height));
	//printf("pos on plane: ");
	//vec3f_print(pos_on_plane);
	//printf("x, y: %d %d\n", bump_x, bump_y);
	//printf("width, height %d %d\n", plane.bump_map.width, plane.bump_map.height);
	//printf("before modulo %d %d\n", plane.bump_map.width, plane.bump_map.height);
	normal.x += (float)plane.bump_map.data[bump_x * plane.bump_map.bytes_per_pixel + bump_y * plane.bump_map.bytes_per_row] / 128. - 1.;
	normal.y += (float)plane.bump_map.data[bump_x * plane.bump_map.bytes_per_pixel + bump_y * plane.bump_map.bytes_per_row + 1] / 128. - 1.;
	normal.z += (float)plane.bump_map.data[bump_x * plane.bump_map.bytes_per_pixel + bump_y * plane.bump_map.bytes_per_row + 2] / 128. - 1.;
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
