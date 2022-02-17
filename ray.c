#include "miniRT.h"
#include <math.h>

#define MAX_BOUNCES 1

t_ray	new_ray(t_ray r, t_vec3f norm_dir, float hit_min)
{
	r.origin = at(r, hit_min);
	r.dir = f_reflection(r.dir, norm_dir);
	return (r);
}

t_vec3f	spot_and_ambient(t_ray r, t_vec3f object_color, \
	t_scene *scene, t_vec3f norm_dir)
{
	t_vec3f				spot_color;
	t_vec3f				ambient_color;

	if (scene->light && scene->light->brightness)
	{
		spot_color = spot_light(r.origin, norm_dir, scene);
		spot_color = vec3f_mul_v(spot_color, object_color);
	}
	else
		spot_color = vec3f_init(0, 0, 0);
	if (scene->ambient && scene->ambient->brightness)
	{
		ambient_color = vec3f_mul(scene->ambient->color, \
				scene->ambient->brightness);
		ambient_color = vec3f_mul_v(ambient_color, object_color);
	}
	else
		ambient_color = vec3f_init(0, 0, 0);
	return (vec3f_add(spot_color, ambient_color));
}

void	get_hit(t_hits *hit, t_scene *scene, t_ray r)
{
	hit->hit_min = 0.;
	hit->hit_side_cylinder = 0;
	sphere_loop(r, scene, hit);
	plane_loop(r, scene, hit);
	cylinder_loop(r, scene, hit);
}

t_vec3f	ray_color(t_ray r, t_scene *scene)
{
	t_vec3f				norm_dir;
	t_vec3f				object_color;
	t_hits				hit;

	get_hit(&hit, scene, r);
	if (hit.hit_min > 0)
	{
		if (hit.hit_type == SPHERE)
			object_color = get_sphere_norm_color(hit, r, scene->spheres.data,
					&norm_dir);
		else if (hit.hit_type == PLANE)
			object_color = get_plane_norm_color(hit, r, scene->planes.data,
					&norm_dir);
		else
			object_color = get_cylinder_norm_color(hit, r,
					scene->cylinders.data, &norm_dir);
		r = new_ray(r, norm_dir, hit.hit_min);
		return (spot_and_ambient(r, object_color, scene, norm_dir));
	}
	return (vec3f_init(0, 0, 0));
}
