#include "miniRT.h"
#include <math.h>

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

void	plane_loop(t_ray r, t_scene *scene, float *hit_min, t_scene_elem_type *hit_type, int *num)
{
	int			i;
	t_plane		plane;
	t_plane		*planes;
	float		hit;

	planes = scene->planes.data;
	i = 0;
	while (i < scene->planes.len)
	{
		plane = planes[i];
		hit = hit_plane(plane.dir, plane.pos, r);
		if (check_hit(hit, hit_min, num, i))
			*hit_type = PLANE;
		i++;
	}
}

void	sphere_loop(t_ray r, t_scene *scene, float *hit_min, t_scene_elem_type *hit_type, int *num)
{
	int			i;
	t_sphere	sphere;
	t_sphere	*spheres;
	float		hit;

	spheres = scene->spheres.data;
	i = 0;
	while (i < scene->spheres.len)
	{
		sphere = spheres[i];
		hit = hit_sphere(sphere, r);
		if (check_hit(hit, hit_min, num, i))
			*hit_type = SPHERE;
		i++;
	}
}

void	cylinder_loop(t_ray r, t_scene *scene, float *hit_min, t_scene_elem_type *hit_type, int *num, int *hit_side_cylinder)
{
	int			i;
	t_cylinder	cylinder;
	t_cylinder	*cylinders;
	float		hit;
	int			hit_side;

	hit_side = 0;
	cylinders = scene->cylinders.data;
	i = 0;
	while (i < scene->cylinders.len)
	{
		cylinder = cylinders[i];
		hit = hit_cylinder(cylinder, r, &hit_side);
		if (check_hit(hit, hit_min, num, i))
		{
			*hit_type = CYLINDER;
			*hit_side_cylinder = hit_side;
		}
		i++;
	}
}

