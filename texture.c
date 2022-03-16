#include "miniRT.h"
#include <math.h>

t_vec3f read_bump(t_bmp bump_map, int x, int y, t_vec3f normal)
{
	int index;
	t_vec3f bump_normal;
	t_angle	angle;

	index = x * bump_map.bytes_per_pixel
		+ y * bump_map.bytes_per_row;
	bump_normal.x = (float)bump_map.data[index] / 128. - 1.;
	bump_normal.y = (float)bump_map.data[index + 1] / 128. - 1.;
	bump_normal.z = -((float)bump_map.data[index + 2] / 128. - 1.);
	angle = get_angle_to(normal, vec3f_init(0, 0, -1));
	if (normal.z < 0)
		angle.angle = M_PI - angle.angle;
	bump_normal = ft_rodrigues(bump_normal, angle.k, angle.angle);
	normal = vec3f_add(normal, bump_normal);
	normal = vec3f_unit(normal);
	return (normal);
}
