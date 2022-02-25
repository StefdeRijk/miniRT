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
	b = (r.origin.x * r.dir.x) + (r.origin.z * r.dir.z) - \
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
