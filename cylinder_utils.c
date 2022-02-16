#include "miniRT.h"

int	ray_in_right_dir(t_ray r, t_cylinder cylinder)
{
	if (r.origin.y > cylinder.height / 2 || r.origin.y < -(cylinder.height / 2))
	{
		if (r.origin.y * r.dir.y >= 0)
			return (0);
	}
	return (1);
}

float	hit_top_or_bottom(t_ray ray, t_cylinder cylinder)
{
	float	t_plane;
	t_vec3f	p1;

	t_plane = -(ray.origin.y - signf(ray.origin.y) * \
		(cylinder.height / 2)) / ray.dir.y;
	p1 = at(ray, t_plane);
	if (p1.x * p1.x + p1.z * p1.z <= cylinder.radius * cylinder.radius)
		return (t_plane);
	return (-1.0);
}
