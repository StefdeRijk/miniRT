#include "vec.h"
#include <math.h>

int	vec3f_equal(t_vec3f v1, t_vec3f v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}

static int	almost_equal(float f1, float f2)
{
	float	e;

	e = 0.000001;
	return (f1 + e >= f2 && f1 - e <= f2);
}

int	vec3f_almost_equal(t_vec3f v1, t_vec3f v2)
{
	return (almost_equal(v1.x, v2.x) && almost_equal(v1.y, v2.y) && \
		almost_equal(v1.z, v2.z));
}
