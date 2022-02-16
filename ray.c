#include "miniRT.h"
#include <math.h>

#define MAX_BOUNCES 1

t_ray	new_ray(t_ray r, t_vec3f norm_dir, float hit_min)
{
	r.origin = at(r, hit_min);
	r.dir = f_reflection(r.dir, norm_dir);
	return (r);
}

t_vec3f	spot_and_ambient(t_ray r, t_vec3f object_color, t_scene *scene, t_vec3f norm_dir)
{
	t_vec3f				spot_color;
	t_vec3f				ambient_color;

	spot_color = spot_light(r.origin, norm_dir, scene);
	spot_color = vec3f_mul_v(spot_color, object_color);
	ambient_color = vec3f_mul(scene->ambient->color, scene->ambient->brightness);
	ambient_color = vec3f_mul_v(ambient_color, object_color);
	return (vec3f_add(spot_color, ambient_color));
}

t_vec3f	ray_color(t_ray r, t_scene *scene)
{
	t_vec3f				norm_dir;
	t_sphere			*spheres;
	t_sphere			sphere;
	t_plane				*planes;
	t_plane				plane;
	t_cylinder			*cylinders;
	t_cylinder			cylinder;
	int					hit_side_cylinder;
	t_vec3f				object_color;
	t_hits				hit;

	r.dir = vec3f_unit(r.dir);
	spheres = scene->spheres.data;
	planes = scene->planes.data;
	cylinders = scene->cylinders.data;
	hit.hit_min = 0.;
	hit_side_cylinder = 0;
	sphere_loop(r, scene, &hit);
	plane_loop(r, scene, &hit);
	cylinder_loop(r, scene, &hit, &hit_side_cylinder);
	if (hit.hit_min > 0)
	{
		if (hit.hit_type == SPHERE)
		{
			sphere = spheres[hit.object_index];
			norm_dir = get_normal_sphere(at(r, hit.hit_min), sphere.pos);
			object_color = sphere.color;
		}
		if (hit.hit_type == PLANE)
		{
			plane = planes[hit.object_index];
			norm_dir = plane_normal(plane.dir, r.dir);
			object_color = plane.color;
		}
		if (hit.hit_type == CYLINDER)
		{
			cylinder = cylinders[hit.object_index];
			if (hit_side_cylinder)
				norm_dir = cylinder_side_norm(at(r, hit.hit_min), cylinder);
			else
				norm_dir = plane_normal(cylinder.dir, r.dir);
			object_color = cylinder.color;
		}
		r = new_ray(r, norm_dir, hit.hit_min);
		return (spot_and_ambient(r, object_color, scene, norm_dir));
	}
	return (vec3f_init(0, 0, 0));
}
