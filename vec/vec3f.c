#include "vec.h"
#include <math.h>
#include <stdio.h>

t_vec3f	vec3f_init(float x, float y, float z)
{
	t_vec3f	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

void vec3f_print(t_vec3f v)
{
	printf("(%f, %f, %f\n", v.x, v.y, v.z);
}

t_vec3f	vec3f_trans(t_vec3f v, t_direction dir, float distance)
{
	if (dir == UP)
	{
		v.x = v.x;
		v.y = v.y - distance;
	}
	if (dir == DOWN)
	{
		v.x = v.x;
		v.y = v.y + distance;
	}
	if (dir == LEFT)
	{
		v.x = v.x - distance;
		v.y = v.y;
	}
	if (dir == RIGHT)
	{
		v.x = v.x + distance;
		v.y = v.y;
	}
	return (v);
}

float vec3f_dot(t_vec3f v1, t_vec3f v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vec3f	vec3f_cross(t_vec3f v1, t_vec3f v2)
{
	float	x;
	float	y;
	float	z;

	x = v1.y * v2.z - v1.z * v2.y;
	y = v1.z * v2.x - v1.x * v2.z;
	z = v1.x * v2.y - v1.y * v2.x;
	return (vec3f_init(x, y, z));
}

float vec3f_len_sq(t_vec3f v)
{
	return (vec3f_dot(v, v));
}

float vec3f_len(t_vec3f v)
{
	return (sqrtf(vec3f_len_sq(v)));
}

t_vec3f vec3f_div(t_vec3f v, float f)
{
	t_vec3f q;

	q = v;
	q.x /= f;
	q.y /= f;
	q.z /= f;
	return (q);
}

t_vec3f vec3f_mul(t_vec3f v, float f)
{
	t_vec3f p;

	p = v;
	p.x *= f;
	p.y *= f;
	p.z *= f;
	return (p);
}

t_vec3f vec3f_sub(t_vec3f v1, t_vec3f v2)
{
	t_vec3f s;

	s = v1;
	s.x -= v2.x;
	s.y -= v2.y;
	s.z -= v2.z;
	return (s);
}

t_vec3f vec3f_add(t_vec3f v1, t_vec3f v2)
{
	t_vec3f s;

	s = v1;
	s.x += v2.x;
	s.y += v2.y;
	s.z += v2.z;
	return (s);
}

t_vec3f vec3f_mul_v(t_vec3f v1, t_vec3f v2)
{
	t_vec3f s;

	s = v1;
	s.x *= v2.x;
	s.y *= v2.y;
	s.z *= v2.z;
	return (s);
}

t_vec3f vec3f_unit(t_vec3f v)
{
	return (vec3f_mul(v, 1 / vec3f_len(v)));
}
