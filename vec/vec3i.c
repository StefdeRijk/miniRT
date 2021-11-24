#include "vec.h"

t_vec3i	vec3i_init(int x, int y, int z)
{
	t_vec3i	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}
