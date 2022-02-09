#include "miniRT.h"
#include <math.h>

t_vec3f at(t_ray r, float t)
{
	return (vec3f_add(r.origin, vec3f_mul(r.dir, t)));
}

int	vec_to_color(t_vec3f v)
{
	return (trgb_to_int(0, fabs(v.x) * 255, fabs(v.y) * 255,
			fabs(v.z) * 255));
}

int	ray_color(t_ray r, t_sphere sphere)
{
	t_vec3f	unit_dir;
	float	hit;

	unit_dir = vec3f_unit(r.dir);
	hit = hit_sphere(sphere, r);
	if (hit > 0)
		unit_dir = vec3f_unit(vec3f_sub(at(r, hit), sphere.pos));
	return (vec_to_color(unit_dir));
}
