#include "miniRT.h"
#include <math.h>

int	ray_in_right_dir_paraboloid(t_ray r)
{
	if (r.origin.y < 0)
	{
		if (r.origin.y * r.dir.y >= 0)
			return (0);
	}
	return (1);
}

float	get_t_paraboloid(t_paraboloid paraboloid, t_ray r)
{
	float	a;
	float	b;
	float	c;
	float	solution;
	int		solved;

	a = powf(r.dir.x, 2) + powf(r.dir.z, 2);
	b = 2 * (r.origin.x * r.dir.x) + 2 * (r.origin.z * r.dir.z) - \
		(r.dir.y * paraboloid.curvature);
	c = powf(r.origin.x, 2) + powf(r.origin.z, 2) - \
		(r.origin.y * paraboloid.curvature);
	solution = abc(a, b, c, &solved);
	if (!solved)
		return (-1.0);
	return (solution);
}

float	hit_paraboloid(t_paraboloid paraboloid, t_ray r)
{
	t_ray	rot_r;
	float	t;

	rot_r = rotate_ray(r, paraboloid.pos, paraboloid.dir);
	if (!ray_in_right_dir_paraboloid(rot_r))
		return (-1.0);
	t = get_t_paraboloid(paraboloid, rot_r);
	return (t);
}

t_vec3f	paraboloid_normal(t_paraboloid paraboloid, t_ray r, t_hits hit)
{
	t_ray	rot_r;
	t_vec3f	hit_to_focal;
	t_vec3f	norm_dir;
	t_angle	angle;
	float	focal_point;

	rot_r = rotate_ray(r, paraboloid.pos, paraboloid.dir);
	focal_point = paraboloid.curvature / 4;
	hit_to_focal = vec3f_unit(vec3f_sub(vec3f_init(0, focal_point, 0), \
		at(rot_r, hit.hit_min)));
	norm_dir = vec3f_div(vec3f_add(hit_to_focal, vec3f_init(0, 1, 0)), 2.);
	norm_dir = vec3f_mul(norm_dir, -1.);
	angle = get_angle(vec3f_mul(paraboloid.dir, -1.0));
	norm_dir = ft_rodrigues(norm_dir, angle.k, angle.angle);
	norm_dir = vec3f_unit(norm_dir);
	return (norm_dir);
}
