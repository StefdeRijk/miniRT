#include "vec.h"

t_vec3f	vec3f_init(float x, float y, float z)
{
	t_vec3f	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
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
