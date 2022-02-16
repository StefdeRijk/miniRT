#include "miniRT.h"
#include <math.h>

t_vec3f	ft_rodrigues(t_vec3f v, t_vec3f k, float angle)
{
	t_vec3f	term_1;
	t_vec3f	term_2;
	t_vec3f	term_3;
	t_vec3f	rotated;

	term_1 = vec3f_mul(v, cos(angle));
	term_2 = vec3f_mul(vec3f_cross(k, v), sin(angle));
	term_3 = vec3f_mul(k, (vec3f_dot(k, v) * (1 - cos(angle))));
	rotated = vec3f_add(term_1, term_2);
	rotated = vec3f_add(rotated, term_3);
	return (rotated);
}

float	abc(float a, float b, float c, int *solved)
{
	float	d;

	d = b * b - 4 * a * c;
	if (d < 0)
	{
		*solved = 0;
		return (0);
	}
	else
	{
		*solved = 1;
		return ((-b - sqrt(d)) / (2.0 * a));
	}
}

float	signf(float a)
{
	if (a < 0)
		return (-1.0);
	return (1.0);
}

t_vec3f	at(t_ray r, float t)
{
	return (vec3f_add(r.origin, vec3f_mul(r.dir, t)));
}
