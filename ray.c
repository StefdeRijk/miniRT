#include "miniRT.h"
#include <math.h>

int	ray_color(t_ray r, t_sphere sphere)
{
	t_vec3f	unit_dir;

	unit_dir = vec3f_unit(r.dir);
	if (hit_sphere(sphere, r))
	{
		return (rgb_to_color(sphere.color));
	}
	printf("%f ", unit_dir.x);
	return (trgb_to_int(0, fabs(unit_dir.x) * 255, fabs(unit_dir.y) * 255,
			fabs(unit_dir.z) * 255));
}
