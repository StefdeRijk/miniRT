#include "miniRT.h"

#define SPOT_BRIGHTNESS 70

int	in_shadow(t_vec3f spot_unit, t_vec3f pos, t_scene *scene, t_vec3f normal)
{
	t_ray	to_spot;
	t_hits	hit;
	t_vec3f	offset;
	float	distance_to_spot;

	to_spot.dir = spot_unit;
	offset = vec3f_mul(normal, 0.000001);
	to_spot.origin = vec3f_add(pos, offset);
	get_hit(&hit, scene, to_spot);
	distance_to_spot = vec3f_len(vec3f_sub(scene->light->pos, pos));
	if (hit.hit_min > 0 && hit.hit_min < distance_to_spot)
		return (1);
	return (0);
}

t_vec3f	spot_light(t_vec3f pos, t_vec3f normal, t_scene *scene)
{
	t_vec3f		spot_unit;
	t_vec3f		spot_color;
	float		distance_sq;
	float		in_product;

	spot_unit = vec3f_sub(scene->light->pos, pos);
	distance_sq = vec3f_len_sq(spot_unit);
	spot_unit = vec3f_unit(spot_unit);
	in_product = vec3f_dot(spot_unit, normal);
	if (in_product < 0 || in_shadow(spot_unit, pos, scene, normal))
		return (vec3f_init(0, 0, 0));
	spot_color = vec3f_mul(scene->light->color,
			((scene->light->brightness * in_product) / distance_sq)
			* SPOT_BRIGHTNESS);
	return (spot_color);
}
