#include "miniRT.h"
#include <math.h>

#define MAX_BOUNCES 1

t_vec3f	ray_color(t_ray r, t_scene *scene)
{
	t_vec3f				norm_dir;
	t_vec3f				direction;
	t_vec3f				ambient_color;
	float				hit_min;
	t_sphere			*spheres;
	t_sphere			sphere;
	int					num;
	t_plane				*planes;
	t_plane				plane;
	t_cylinder			*cylinders;
	t_cylinder			cylinder;
	t_vec3f				spot_color;
	t_scene_elem_type	hit_type;
	int					hit_side_cylinder;
	t_vec3f				color;


	r.dir = vec3f_unit(r.dir);
	spheres = scene->spheres.data;
	planes = scene->planes.data;
	cylinders = scene->cylinders.data;
	hit_min = 0.;
	hit_side_cylinder = 0;
	sphere_loop(r, scene, &hit_min, &hit_type, &num);
	plane_loop(r, scene, &hit_min, &hit_type, &num);
	cylinder_loop(r, scene, &hit_min, &hit_type, &num, &hit_side_cylinder);
	if (hit_min > 0)
	{
		if (hit_type == SPHERE)
		{
			sphere = spheres[num];
			norm_dir = get_normal_sphere(at(r, hit_min), sphere.pos);
			color = sphere.color;
		}
		if (hit_type == PLANE)
		{
			plane = planes[num];
			norm_dir = plane_normal(plane.dir, r.dir);
			color = plane.color;
		}
		if (hit_type == CYLINDER)
		{
			cylinder = cylinders[num];
			if (hit_side_cylinder)
				norm_dir = cylinder_side_norm(at(r, hit_min), cylinder);
			else
				norm_dir = plane_normal(cylinder.dir, r.dir);
			color = cylinder.color;
		}
		direction = f_reflection(r.dir, norm_dir);
		r.origin = at(r, hit_min);
		r.dir = direction;
		spot_color = spot_light(r.origin, norm_dir, scene);
		spot_color = vec3f_mul_v(spot_color, color);
		ambient_color = vec3f_mul(scene->ambient->color, scene->ambient->brightness);
		ambient_color = vec3f_mul_v(ambient_color, color);
		return (vec3f_add(spot_color, ambient_color));
	}
	// if (scene->light && hit_light)
	// 	return (spot_light(r, scene));
	return (vec3f_init(0, 0, 0));
}
