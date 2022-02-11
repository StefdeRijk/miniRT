#include "miniRT.h"
#include <math.h>

#define MAX_BOUNCES 5

t_vec3f	at(t_ray r, float t)
{
	return (vec3f_add(r.origin, vec3f_mul(r.dir, t)));
}

int	vec_to_color(t_vec3f v)
{
	return (trgb_to_int(0, v.x * 255, v.y * 255,
			v.z * 255));
}

t_vec3f	f_reflection(t_vec3f incoming, t_vec3f normal)
{
	t_vec3f	refl;

	refl = vec3f_sub(incoming, (vec3f_mul(normal, 2 * vec3f_dot(incoming, normal))));
	return (refl);
}

t_vec3f	get_normal_sphere(t_vec3f hit_point, t_vec3f sphere_center)
{
	return (vec3f_unit(vec3f_sub(hit_point, sphere_center)));
}

t_vec3f	ray_color(t_ray r, t_scene *scene)
{
	t_vec3f		unit_dir;
	t_vec3f		norm_dir;
	t_vec3f		reflection;
	float		hit;
	float		hit_min;
	t_sphere	*spheres;
	t_sphere	sphere;
	int			sphere_num;
	t_plane		*planes;
	t_plane		plane;
	int			plane_num;
	int			i;
	t_scene_elem_type	hit_type;

	unit_dir = vec3f_unit(r.dir);
	spheres = scene->spheres.data;
	planes = scene->planes.data;
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
			hit_type = SPHERE;
		}
		i++;
	}
	i = 0;
	while (i < scene->planes.len && r.bounces < MAX_BOUNCES)
	{
		plane = planes[i];
		hit = hit_plane(plane, r);
		if (hit > 0 && (hit < hit_min || hit_min == 0.))
		{
			hit_min = hit;
			plane_num = i;
			hit_type = PLANE;
		}
		i++;
	}
	if (hit_min > 0 && r.bounces < MAX_BOUNCES)
	{
		if (hit_type == SPHERE)
		{
			sphere = spheres[sphere_num];
			// if (sphere.material == 's')
			// {
				// norm_dir = vec3f_unit(vec3f_sub(at(r, hit_min), sphere.pos));
				// reflection = = vec3f_sub(r.dir, (vec3f_mul(norm_dir, 2 * vec3f_dot(r.dir, norm_dir))));
				norm_dir = get_normal_sphere(at(r, hit_min), sphere.pos);
				reflection = f_reflection(r.dir, norm_dir);
			// }
			r.origin = at(r, hit_min);
			r.dir = reflection;
			r.bounces++;
			return (vec3f_mul_v(sphere.color, ray_color(r, scene)));
		}
		if (hit_type == PLANE)
		{
			plane = planes[plane_num];
			unit_dir = vec3f_unit(vec3f_sub(at(r, hit_min), plane.pos));
			r.origin = at(r, hit_min);
			r.dir = unit_dir;
			r.bounces++;
			return (vec3f_mul_v(plane.color, ray_color(r, scene)));
		}
	}
	if (scene->light && r.bounces > 0)
		return (spot_light(r, scene));
	return (vec3f_mul(scene->ambient->color, scene->ambient->brightness));
}
