#include "miniRT.h"
#include <math.h>

t_vec3f	at(t_ray r, float t)
{
	return (vec3f_add(r.origin, vec3f_mul(r.dir, t)));
}

int	vec_to_color(t_vec3f v)
{
	return (trgb_to_int(0, fabs(v.x) * 255, fabs(v.y) * 255,
			fabs(v.z) * 255));
}

int	ray_color(t_ray r, t_info *info, t_scene *scene)
{
	t_vec3f		unit_dir;
	float		hit;
	float		hit_min;
	int			color;
	t_vec3f		sphere_color;
	t_vec3i		color_int;
	t_sphere	*spheres;
	t_sphere	sphere;
	int			sphere_num;
	int			i;

	unit_dir = vec3f_unit(r.dir);
	spheres = scene->spheres.data;
	hit_min = 0.;
	i = 0;
	while (i < scene->spheres.len)
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
	if (hit_min > 0)
	{
		sphere = spheres[sphere_num];
		unit_dir = vec3f_unit(vec3f_sub(at(r, hit_min), sphere.pos));
		sphere_color = vec3f_mul_v(sphere.color, scene->ambient->color);
		sphere_color = vec3f_mul(sphere_color, scene->ambient->brightness);
		color_int = float_to_color_vec(sphere_color);
		color = rgb_to_color(color_int);
		return (color);
	}
	return (vec_to_color(unit_dir));
}
