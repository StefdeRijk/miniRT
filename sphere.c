#include "miniRT.h"

int	hit_sphere(t_sphere sphere, t_ray r)
{
	t_vec3f oc = vec3f_sub(r.origin, sphere.pos);
	float a = vec3f_len_sq(r.dir);
	float b = 2.0 * vec3f_dot(oc, r.dir);
	float c = vec3f_len_sq(oc) - (sphere.radius * sphere.radius);
	float d = b*b - 4*a*c;

	return (d > 0);
}

