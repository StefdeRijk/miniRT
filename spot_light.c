#include "miniRT.h"
#include <math.h>

#define SPOT_BRIGHTNESS 70

int	get_prev_ray_hit(t_scene *scene)
{
	if (scene->prev_hit == SPHERE)
		return (0);
	if (scene->prev_hit == PLANE)
		return (1);
	if (scene->prev_hit == CYLINDER)
		return (2);
	return (0);
}

void	shadow_loop(int i, t_ray r, t_scene *scene, t_hits *hit)
{
	if (i == 0)
	{
		scene->prev_hit = SPHERE;
		sphere_loop_shadow(r, scene, hit);
	}
	else if (i == 1)
	{
		scene->prev_hit = PLANE;
		plane_loop_shadow(r, scene, hit);
	}
	else if (i == 2)
	{
		scene->prev_hit = CYLINDER;
		cylinder_loop_shadow(r, scene, hit);
	}
}

int	get_hit_shadow(t_scene *scene, t_ray r, t_vec3f pos)
{
	t_hits	hit;
	int		loop_index;
	int		i;

	hit.hit_min = 0.;
	hit.hit_side_cylinder = 0;
	scene->distance_to_spot = vec3f_len(vec3f_sub(scene->light->pos, pos));
	i = 0;
	loop_index = get_prev_ray_hit(scene);
	while (i < 3)
	{
		shadow_loop(loop_index, r, scene, &hit);
		if (hit.hit_min > 0 && hit.hit_min < scene->distance_to_spot)
			return (1);
		loop_index = (loop_index + 1) % 3;
		i++;
	}
	return (0);
}

int	in_shadow(t_vec3f spot_unit, t_vec3f pos, t_scene *scene, t_ray r)
{
	t_ray	to_spot;
	t_vec3f	reverse_r_dir;
	t_vec3f	offset;

	to_spot.dir = spot_unit;
	reverse_r_dir = vec3f_sub(vec3f_init(0, 0, 0), r.dir);
	offset = vec3f_mul(reverse_r_dir, 0.1);
	to_spot.origin = vec3f_add(pos, offset);
	if (get_hit_shadow(scene, to_spot, pos))
		return (1);
	return (0);
}

t_vec3f	spot_light_specular(t_vec3f normal, t_scene *scene, t_ray new_r, t_ray old_r)
{
	t_vec3f		spot_dir;
	t_vec3f		spot_color_specular;
	float		in_product_specular;
	float		alpha;
	float		distance_sq;
	t_vec3f		reverse_ray;
	t_vec3f		reflected_spot;

	alpha = 20;
	spot_dir = vec3f_sub(scene->light->pos, new_r.origin);
	distance_sq = vec3f_len_sq(spot_dir);
	reverse_ray = vec3f_mul(old_r.dir, 1.); //WHY not -1?
	reflected_spot = f_reflection(spot_dir, normal);
	reflected_spot = vec3f_unit(reflected_spot);
	reverse_ray = vec3f_unit(reverse_ray);
	in_product_specular = vec3f_dot(reflected_spot, reverse_ray);
	if (in_product_specular < 0 || in_shadow(vec3f_unit(spot_dir), new_r.origin, scene, old_r))
		return (vec3f_init(0, 0, 0));
	spot_color_specular = vec3f_mul(scene->light->color, \
		((scene->light->brightness * powf(in_product_specular, alpha)) / distance_sq) \
		* SPOT_BRIGHTNESS);
	return (spot_color_specular);
}

t_vec3f	spot_light(t_ray new_r, t_vec3f normal, t_scene *scene, t_ray old_r)
{
	t_vec3f		spot_unit;
	t_vec3f		spot_color_diffuse;
	float		distance_sq;
	float		in_product;

	spot_unit = vec3f_sub(scene->light->pos, new_r.origin);
	distance_sq = vec3f_len_sq(spot_unit);
	spot_unit = vec3f_unit(spot_unit);
	in_product = vec3f_dot(spot_unit, normal);
	if (in_product < 0 || in_shadow(spot_unit, new_r.origin, scene, old_r))
		return (vec3f_init(0, 0, 0));
	spot_color_diffuse = vec3f_mul(scene->light->color, \
		((scene->light->brightness * in_product) / distance_sq) \
		* SPOT_BRIGHTNESS);
	return (spot_color_diffuse);
}
