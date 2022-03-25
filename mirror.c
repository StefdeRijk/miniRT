#include "miniRT.h"

t_vec3f	f_reflection(t_vec3f incoming, t_vec3f normal)
{
	t_vec3f	refl;

	refl = vec3f_sub(incoming, \
		(vec3f_mul(normal, 2 * vec3f_dot(incoming, normal))));
	return (refl);
}

t_vec3f	get_color_mirror(t_vec3f norm_dir, t_ray r, \
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
