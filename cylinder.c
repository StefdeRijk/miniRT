#include "miniRT.h"
#include <math.h>

t_vec3f	ft_rodrigues(t_vec3f v, t_vec3f k, float angle)
{
	t_vec3f	term_1;
	t_vec3f	term_2;
	t_vec3f	term_3;
	t_vec3f	rotated;

	term_1 = vec3f_mul(v, cos(angle));
	term_2 = vec3f_mul(vec3f_cross(k, v), sin(angle));
	term_3 = vec3f_mul(k, (vec3f_dot(k, v) * (1 - cos(angle))));
	rotated = vec3f_add(term_1, term_2);
	rotated = vec3f_add(rotated, term_3);
	return (rotated);
}

float   hit_cylinder(t_cylinder cylinder, t_ray r)
{
	t_vec3f	k;
	t_vec3f	norm_ray_dir;
	t_vec3f	norm_cyl_dir;
	t_vec3f	rotated_dir;
	t_vec3f	rotated_origin;
	t_vec3f	rot_plane;
	t_vec3f	shifted_origin;
	float	len_rot_plane;
	float	angle;

	norm_cyl_dir = vec3f_unit(cylinder.dir);
	norm_ray_dir = vec3f_unit(r.dir);
	rot_plane = vec3f_cross(cylinder.dir, vec3f_init(0, 1, 0));
	len_rot_plane = vec3f_len(rot_plane);
	angle = asin(len_rot_plane);
	k = vec3f_unit(rot_plane);
	rotated_dir = ft_rodrigues(r.dir, k, angle);
	rotated_origin = ft_rodrigues(r.origin, k, angle);
	shifted_origin = vec3f_sub(rotated_origin, cylinder.pos);
	if (shifted_origin.y > cylinder.height / 2 || shifted_origin.y < -(cylinder.height / 2))
		if (shifted_origin.y * rotated_dir.y < 0)
			return (-1);
	return (0.8);
}
