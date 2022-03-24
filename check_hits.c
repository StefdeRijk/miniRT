#include "miniRT.h"

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

void	plane_loop(t_ray r, t_scene *scene, t_hits *hits)
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
		if (check_hit(hit, &hits->hit_min, &hits->object_index, i))
		{
			hits->hit_type = PLANE;
			hits->material = plane.material;
		}
		i++;
	}
}

void	sphere_loop(t_ray r, t_scene *scene, t_hits *hits)
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
		if (check_hit(hit, &hits->hit_min, &hits->object_index, i))
		{
			hits->hit_type = SPHERE;
			hits->material = sphere.material;
		}
		i++;
	}
}

void	cylinder_loop(t_ray r, t_scene *scene, t_hits *hits)
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
		if (check_hit(hit, &hits->hit_min, &hits->object_index, i))
		{
			hits->hit_type = CYLINDER;
			hits->hit_side_cylinder = hit_side;
			hits->material = cylinder.material;
		}
		i++;
	}
}

void	paraboloid_loop(t_ray r, t_scene *scene, t_hits *hits)
{
	int				i;
	t_paraboloid	paraboloid;
	t_paraboloid	*paraboloids;
	float			hit;

	paraboloids = scene->paraboloids.data;
	i = 0;
	while (i < scene->paraboloids.len)
	{
		paraboloid = paraboloids[i];
		hit = hit_paraboloid(paraboloid, r);
		if (check_hit(hit, &hits->hit_min, &hits->object_index, i))
		{
			hits->hit_type = PARABOLOID;
			hits->material = paraboloid.material;
		}
		i++;
	}
}
