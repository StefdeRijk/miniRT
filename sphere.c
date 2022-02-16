#include "miniRT.h"
#include <math.h>

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
