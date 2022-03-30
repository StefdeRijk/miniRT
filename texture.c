#include "miniRT.h"
#include <math.h>

t_vec3f	rotate_bump_to_sphere_normal(t_vec3f bump_normal, t_vec3f normal)
{
	t_vec3f	t;
	t_vec3f	b;
	t_vec3f	c[3];
	t_vec3f	result;
	t_vec3f	p;

	p = normal;
	p.y = 0;
	p = vec3f_unit(p);
	t = vec3f_unit(vec3f_init(-p.z, 0, p.x));
	b = vec3f_cross(normal, t);
	c[0] = vec3f_mul(t, bump_normal.x);
	c[1] = vec3f_mul(b, bump_normal.y);
	c[2] = vec3f_mul(normal, bump_normal.z);
	result = (vec3f_unit((vec3f_add(c[0], vec3f_add(c[1], c[2])))));
	result = vec3f_mul(result, -1);
	return (result);
}

t_vec3f	read_bump(t_bmp bump_map, int index)
{
	t_vec3f	bump_normal;

	bump_normal.x = (float)bump_map.data[index] / 128. - 1.;
	bump_normal.y = (float)bump_map.data[index + 1] / 128. - 1.;
	bump_normal.z = -((float)bump_map.data[index + 2] / 128. - 1.);
	return (bump_normal);
}
