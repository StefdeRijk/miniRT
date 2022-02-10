#include "miniRT.h"
#include <math.h>

#define MAX_BOUNCES 1

t_vec3f	at(t_ray r, float t)
{
	return (vec3f_add(r.origin, vec3f_mul(r.dir, t)));
}

int	vec_to_color(t_vec3f v)
{
	return (trgb_to_int(0, fabs(v.x) * 255, fabs(v.y) * 255,
			fabs(v.z) * 255));
}

t_vec3f	ray_color(t_ray r, t_info *info, t_scene *scene)
{
	t_vec3f		unit_dir;
	float		hit;
	float		hit_min;
	t_sphere	*spheres;
	t_sphere	sphere;
	int			sphere_num;
	t_vec3f		spot_direction;
	t_vec3f		spot_unit;
	t_vec3f		ray_unit;
	float		in_product;
	t_vec3f		ambient_color;
	t_vec3f		spot_color;
	int			i;

	unit_dir = vec3f_unit(r.dir);
	spheres = scene->spheres.data;
	hit_min = 0.;
	i = 0;
	while (i < scene->spheres.len && r.bounces < MAX_BOUNCES)
	{
		sphere = spheres[i];
		hit = hit_sphere(sphere, r);
		if (hit > 0 && (hit < hit_min || hit_min == 0.))
		{
			hit_min = hit;
			sphere_num = i;
		}
		i++;
	}
	if (hit_min > 0 && r.bounces < MAX_BOUNCES)
	{
		sphere = spheres[sphere_num];
		unit_dir = vec3f_unit(vec3f_sub(at(r, hit_min), sphere.pos));
		r.origin = at(r, hit_min);
		r.dir = unit_dir;
		r.bounces++;
		return (vec3f_mul_v(sphere.color, ray_color(r, info, scene)));
	}
	if (scene->light && r.bounces > 0)
	{
		spot_direction = vec3f_sub(scene->light->pos, r.origin);
		spot_unit = vec3f_unit(scene->light->pos);
		ray_unit = vec3f_unit(r.origin);
		in_product = vec3f_dot(spot_unit, ray_unit);
		if (in_product < 0)
			in_product = 0;
		spot_color = vec3f_mul(scene->light->color, (scene->light->brightness * in_product));
		ambient_color = vec3f_mul(scene->ambient->color, scene->ambient->brightness);
		return (vec3f_add(spot_color, ambient_color));
	}
	return (vec3f_mul(scene->ambient->color, scene->ambient->brightness));
}
