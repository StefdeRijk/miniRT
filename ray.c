#include "miniRT.h"
#include <math.h>

#define MAX_BOUNCES 1

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

t_vec3f	random_in_sphere(void)
{
	t_vec3f	random_point;
	float	x;
	float	y;
	float	z;

	while (1)
	{
		x = (float)rand() / (float)RAND_MAX * 2 - 1;
		y = (float)rand() / (float)RAND_MAX * 2 - 1;
		z = (float)rand() / (float)RAND_MAX * 2 - 1;
		random_point = vec3f_init(x, y, z);
		if (vec3f_len_sq(random_point) <= 1)
			break ;
	}
	return (vec3f_unit(random_point));
}

int	check_hit(float hit, float *hit_min, int *num, int i)
{
	if (hit > 0 && (hit < *hit_min || *hit_min == 0.))
	{
		*hit_min = hit;
		*num = i;
		return (1);
	}
	return (0);
}

t_vec3f	ray_color(t_ray r, t_scene *scene)
{
	t_vec3f		norm_dir;
	t_vec3f		direction;
	t_vec3f		ambient_color;
	float		which_side;
	float		hit;
	float		hit_min;
	t_sphere	*spheres;
	t_sphere	sphere;
	int			sphere_num;
	t_plane		*planes;
	t_plane		plane;
	int			plane_num;
	t_cylinder	*cylinders;
	t_cylinder	cylinder;
	int			cylinder_num;
	int			i;
	int			hit_light;
	t_vec3f		spot_color;
	t_scene_elem_type	hit_type;
	int			hit_side;
	int			hit_side_cylinder;

	r.dir = vec3f_unit(r.dir);
	spheres = scene->spheres.data;
	planes = scene->planes.data;
	cylinders = scene->cylinders.data;
	hit_min = 0.;
	hit_light = 1;
	i = 0;
	hit_side = 0;
	hit_side_cylinder = 0;
	while (i < scene->spheres.len)
	{
		sphere = spheres[i];
		hit = hit_sphere(sphere, r);
		if (check_hit(hit, &hit_min, &sphere_num, i))
			hit_type = SPHERE;
		i++;
	}
	i = 0;
	while (i < scene->planes.len)
	{
		plane = planes[i];
		hit = hit_plane(plane.dir, plane.pos, r);
		if (hit > 0 && (hit < hit_min || hit_min == 0.))
		{
			if (check_hit(hit, &hit_min, &plane_num, i))
				hit_type = PLANE;
		}
		i++;
	}
	i = 0;
	while (i < scene->cylinders.len)
	{
		cylinder = cylinders[i];
		hit = hit_cylinder(cylinder, r, &hit_side);
		if (hit > 0 && (hit < hit_min || hit_min == 0.))
		{
			if (check_hit(hit, &hit_min, &cylinder_num, i))
			{
				hit_type = CYLINDER;
				hit_side_cylinder = hit_side;
			}
		}
		i++;
	}
	if (hit_min > 0)
	{
		if (hit_type == SPHERE)
		{
			sphere = spheres[sphere_num];
			norm_dir = get_normal_sphere(at(r, hit_min), sphere.pos);
			direction = f_reflection(r.dir, norm_dir);
			r.origin = at(r, hit_min);
			r.dir = direction;
			r.bounces++;
			spot_color = spot_light(r.origin, norm_dir, scene);
			spot_color = vec3f_mul_v(spot_color, sphere.color);
			ambient_color = vec3f_mul(scene->ambient->color, scene->ambient->brightness);
			ambient_color = vec3f_mul_v(ambient_color, sphere.color);
			return (vec3f_add(spot_color, ambient_color));
		}
		if (hit_type == PLANE)
		{
			plane = planes[plane_num];
			which_side = vec3f_dot(plane.dir, r.dir);
			if (which_side > 0.)
				norm_dir = vec3f_sub(vec3f_init(0, 0, 0), vec3f_unit(plane.dir));
			else
				norm_dir = vec3f_unit(plane.dir);
			direction = f_reflection(r.dir, norm_dir);
			r.origin = at(r, hit_min);
			r.dir = direction;
			r.bounces++;
			spot_color = spot_light(r.origin, norm_dir, scene);
			spot_color = vec3f_mul_v(spot_color, plane.color);
			ambient_color = vec3f_mul(scene->ambient->color, scene->ambient->brightness);
			ambient_color = vec3f_mul_v(ambient_color, plane.color);
			return (vec3f_add(spot_color, ambient_color));
		}
		if (hit_type == CYLINDER)
		{
			cylinder = cylinders[cylinder_num];
			if (hit_side_cylinder)
			{
				t_vec3f hit_pos;
				float distance_to_cylinder_plane;
				t_vec3f hit_pos_in_cylinder_plane;
				t_ray along_cylinder;
				hit_pos = at(r, hit_min);
				along_cylinder.origin = hit_pos;
				along_cylinder.dir = cylinder.dir;
				distance_to_cylinder_plane = hit_plane(cylinder.dir, cylinder.pos, along_cylinder);
				hit_pos_in_cylinder_plane = at(along_cylinder, distance_to_cylinder_plane);
				norm_dir = vec3f_sub(hit_pos_in_cylinder_plane, cylinder.pos);
				direction = f_reflection(r.dir, norm_dir);
				r.origin = at(r, hit_min);
				r.dir = direction;
				r.bounces++;
				spot_color = spot_light(r.origin, norm_dir, scene);
				spot_color = vec3f_mul_v(spot_color, cylinder.color);
				ambient_color = vec3f_mul(scene->ambient->color, scene->ambient->brightness);
				ambient_color = vec3f_mul_v(ambient_color, cylinder.color);
				return (vec3f_add(spot_color, ambient_color));
			}
			which_side = vec3f_dot(cylinder.dir, r.dir);
			if (which_side > 0.)
				norm_dir = vec3f_sub(vec3f_init(0, 0, 0), vec3f_unit(cylinder.dir));
			else
				norm_dir = vec3f_unit(cylinder.dir);
			direction = f_reflection(r.dir, norm_dir);
			r.origin = at(r, hit_min);
			r.dir = direction;
			r.bounces++;
			spot_color = spot_light(r.origin, norm_dir, scene);
			spot_color = vec3f_mul_v(spot_color, cylinder.color);
			ambient_color = vec3f_mul(scene->ambient->color, scene->ambient->brightness);
			ambient_color = vec3f_mul_v(ambient_color, cylinder.color);
			return (vec3f_add(spot_color, ambient_color));
		}
	}
	// if (scene->light && hit_light)
	// 	return (spot_light(r, scene));
	return (vec3f_init(0, 0, 0));
}
