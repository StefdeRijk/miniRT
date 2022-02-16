#include "miniRT.h"

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

void	do_loop(int i, t_ray r, t_scene *scene, t_hits *hit)
{
	if (i == 0)
	{
		scene->prev_hit = SPHERE;
		sphere_loop(r, scene, hit);
	}
	else if (i == 1)
	{
		scene->prev_hit = PLANE;
		plane_loop(r, scene, hit);
	}
	else if (i == 2)
	{
		scene->prev_hit = CYLINDER;
		cylinder_loop(r, scene, hit);
	}
}

int	get_hit_shadow(t_hits *hit, t_scene *scene, t_ray r, t_vec3f pos)
{
	float	distance_to_spot;
	int		loop_index;
	int		i;

	hit->hit_min = 0.;
	hit->hit_side_cylinder = 0;
	distance_to_spot = vec3f_len(vec3f_sub(scene->light->pos, pos));
	i = 0;
	loop_index = get_prev_ray_hit(scene);
	while (i < 3)
	{
		do_loop(loop_index, r, scene, hit);
		if (hit->hit_min > 0 && hit->hit_min < distance_to_spot)
			return (1);
		loop_index = (loop_index + 1) % 3;
		i++;
	}
	return (0);
}

int	in_shadow(t_vec3f spot_unit, t_vec3f pos, t_scene *scene, t_vec3f normal)
{
	t_ray	to_spot;
	t_hits	hit;
	t_vec3f	offset;

	to_spot.dir = spot_unit;
	offset = vec3f_mul(normal, 0.000001);
	to_spot.origin = vec3f_add(pos, offset);
	if (get_hit_shadow(&hit, scene, to_spot, pos))
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
