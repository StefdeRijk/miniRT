#include "miniRT.h"
#include <math.h>

#define SPOT_BRIGHTNESS 70

int	get_hit_shadow(t_light light, t_old_new_ray rays, t_vec3f pos,
		t_scene *scene)
{
	t_hits	hit;
	float	distance_to_spot;

	hit.hit_min = 0;
	hit.hit_side_cylinder = 0;
	distance_to_spot = vec3f_len(vec3f_sub(light.pos, pos));
	objects_loop(rays.n, scene, &hit, distance_to_spot);
	if (hit.hit_min > 0 && hit.hit_min < distance_to_spot)
		return (1);
	return (0);
}

int	in_shadow(t_vec3f pos, t_light light, t_old_new_ray rays, t_scene *scene)
{
	t_ray	to_spot;
	t_vec3f	reverse_r_dir;
	t_vec3f	offset;
	t_vec3f	spot_dir;

	spot_dir = vec3f_unit(vec3f_sub(light.pos, pos));
	to_spot.dir = spot_dir;
	reverse_r_dir = vec3f_sub(vec3f_init(0, 0, 0), rays.o.dir);
	offset = vec3f_mul(reverse_r_dir, 0.0001);
	to_spot.origin = vec3f_add(pos, offset);
	rays.n = to_spot;
	if (get_hit_shadow(light, rays, pos, scene))
		return (1);
	return (0);
}

t_vec3f	spot_light_specular(t_vec3f normal, t_light light, t_old_new_ray rays,
		t_scene *scene)
{
	t_vec3f		spot_dir;
	t_vec3f		spot_color_specular;
	float		in_product_specular;
	float		alpha;
	t_vec3f		reflected_spot;

	alpha = 20;
	spot_dir = vec3f_unit(vec3f_sub(light.pos, rays.n.origin));
	reflected_spot = f_reflection(vec3f_mul(spot_dir, 1.), normal);
	reflected_spot = vec3f_unit(reflected_spot);
	in_product_specular = vec3f_dot(reflected_spot, vec3f_unit(rays.o.dir));
	if (in_product_specular < 0 || in_shadow(rays.n.origin,
			light, rays, scene))
		return (vec3f_init(0, 0, 0));
	spot_color_specular = vec3f_mul(light.color, \
		((light.brightness * powf(in_product_specular, alpha))
				/ vec3f_len_sq(spot_dir)) * SPOT_BRIGHTNESS);
	return (spot_color_specular);
}

t_vec3f	spot_light(t_old_new_ray rays, t_vec3f normal, t_light light,
		t_scene *scene)
{
	t_vec3f		spot_unit;
	t_vec3f		spot_color_diffuse;
	float		distance_sq;
	float		in_product;

	spot_unit = vec3f_sub(light.pos, rays.n.origin);
	distance_sq = vec3f_len_sq(spot_unit);
	spot_unit = vec3f_unit(spot_unit);
	in_product = vec3f_dot(spot_unit, normal);
	if (in_product < 0
		|| in_shadow(rays.n.origin, light, rays, scene))
		return (vec3f_init(0, 0, 0));
	spot_color_diffuse = vec3f_mul(light.color, \
		((light.brightness * in_product) / distance_sq) \
		* SPOT_BRIGHTNESS);
	return (spot_color_diffuse);
}
