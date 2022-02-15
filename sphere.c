#include "miniRT.h"
#include <math.h>

float	hit_sphere(t_sphere sphere, t_ray r)
{
	t_vec3f	oc;
	float	a;
	float	b;
	float	c;
	float	solution;
	int solved;

	oc = vec3f_sub(r.origin, sphere.pos);
	a = vec3f_len_sq(r.dir);
	b = 2.0 * vec3f_dot(oc, r.dir);
	c = vec3f_len_sq(oc) - (sphere.radius * sphere.radius);
	solution = abc(a, b, c, &solved);
	if (!solved)
		return (-1.0);
	return (solution);
}
