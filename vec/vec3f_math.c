#include "vec.h"
#include <math.h>

t_vec3f	vec3f_div(t_vec3f v, float f)
{
	t_vec3f	q;

	q = v;
	q.x /= f;
	q.y /= f;
	q.z /= f;
	return (q);
}

t_vec3f	vec3f_mul(t_vec3f v, float f)
{
	t_vec3f	p;

	p = v;
	p.x *= f;
	p.y *= f;
	p.z *= f;
	return (p);
}

t_vec3f	vec3f_sub(t_vec3f v1, t_vec3f v2)
{
	t_vec3f	s;

	s = v1;
	s.x -= v2.x;
	s.y -= v2.y;
	s.z -= v2.z;
	return (s);
}

t_vec3f	vec3f_add(t_vec3f v1, t_vec3f v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vec3f	vec3f_mul_v(t_vec3f v1, t_vec3f v2)
{
	t_vec3f	s;

	s = v1;
	s.x *= v2.x;
	s.y *= v2.y;
	s.z *= v2.z;
	return (s);
}
