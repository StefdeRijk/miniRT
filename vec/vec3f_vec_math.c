#include "vec.h"
#include <math.h>

float	vec3f_dot(t_vec3f v1, t_vec3f v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vec3f	vec3f_left_cross(t_vec3f v1, t_vec3f v2)
{
	float	x;
	float	y;
	float	z;

	x = v1.z * v2.y - v1.y * v2.z;
	y = v1.x * v2.z - v1.z * v2.x;
	z = v1.y * v2.x - v1.x * v2.y;
	return (vec3f_init(x, y, z));
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

float	vec3f_len_sq(t_vec3f v)
{
	return (vec3f_dot(v, v));
}

float	vec3f_len(t_vec3f v)
{
	return (sqrtf(vec3f_len_sq(v)));
}
