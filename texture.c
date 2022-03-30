#include "miniRT.h"
#include <math.h>

t_vec3f	add_bump_to_normal(t_vec3f bump_normal, t_vec3f normal)
{
	t_angle	angle;
	t_vec3f	added_normal;
	t_vec3f	unit;
	float	x_angle;
	float	y_angle;

	t_vec3f	p = normal;
	p.y = 0;
	p = vec3f_unit(p);
	t_vec3f	t = vec3f_unit(vec3f_init(-p.z, 0, p.x));
	t_vec3f b = vec3f_cross(normal, t);
	t_vec3f c1 = vec3f_mul(t, bump_normal.x);
	t_vec3f c2 = vec3f_mul(b, bump_normal.y);
	t_vec3f c3 = vec3f_mul(normal, bump_normal.z);
	t_vec3f result = (vec3f_unit((vec3f_add(c1, vec3f_add(c2, c3)))));
	result = vec3f_mul(result, -1);
	return (result);
}

t_vec3f	read_bump(t_bmp bump_map, int index, t_vec3f normal)
{
	t_vec3f	bump_normal;

	bump_normal.x = (float)bump_map.data[index] / 128. - 1.;
	bump_normal.y = (float)bump_map.data[index + 1] / 128. - 1.;
	bump_normal.z = -((float)bump_map.data[index + 2] / 128. - 1.);
	return (add_bump_to_normal(bump_normal, normal));
}
