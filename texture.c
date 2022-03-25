#include "miniRT.h"
#include <math.h>

t_vec3f	add_bump_to_normal(t_vec3f bump_normal, t_vec3f normal)
{
	t_angle	angle;
	t_vec3f	added_normal;
	t_vec3f	unit;

	angle = get_angle_to(vec3f_init(0, 0, -1), normal);
	bump_normal = ft_rodrigues(bump_normal, angle.k, angle.angle);
	return (bump_normal);
	added_normal = vec3f_add(normal, bump_normal);
	if (vec3f_almost_equal(added_normal, vec3f_init(0., 0., 0.)))
		added_normal = normal;
	unit = vec3f_unit(added_normal);
	return (unit);
}

t_vec3f	read_bump(t_bmp bump_map, int index, t_vec3f normal)
{
	t_vec3f	bump_normal;

	bump_normal.x = (float)bump_map.data[index] / 128. - 1.;
	bump_normal.y = (float)bump_map.data[index + 1] / 128. - 1.;
	bump_normal.z = -((float)bump_map.data[index + 2] / 128. - 1.);
	return (add_bump_to_normal(bump_normal, normal));
}
