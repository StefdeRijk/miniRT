#include "miniRT.h"

t_vec3f	get_color_mirror_plane(t_vec3f norm_dir, t_ray r, \
	float hit_min, t_scene *scene)
{
	t_vec3f	color;
	t_ray	new_r;

	if (r.bounces > MAX_BOUNCES)
		return (vec3f_init(0, 0, 0));
	new_r = new_ray(r, norm_dir, hit_min);
	color = ray_color(new_r, scene);
	return (color);
}
