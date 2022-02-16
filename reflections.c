#include "miniRT.h"

t_vec3f	f_reflection(t_vec3f incoming, t_vec3f normal)
{
	t_vec3f	refl;

	refl = vec3f_sub(incoming, \
		(vec3f_mul(normal, 2 * vec3f_dot(incoming, normal))));
	return (refl);
}
