#include "miniRT.h"

void	plane_loop_shadow(t_ray r, t_scene *scene, t_hits *hits)
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
		hits->hit_min = hit;
		if (hits->hit_min > 0 && hits->hit_min < scene->distance_to_spot)
			return ;
		i++;
	}
}

void	sphere_loop_shadow(t_ray r, t_scene *scene, t_hits *hits)
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
		hits->hit_min = hit;
		if (hits->hit_min > 0 && hits->hit_min < scene->distance_to_spot)
			return ;
		i++;
	}
}

void	cylinder_loop_shadow(t_ray r, t_scene *scene, t_hits *hits)
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
		hits->hit_min = hit;
		if (hits->hit_min > 0 && hits->hit_min < scene->distance_to_spot)
		{
			hits->hit_side_cylinder = hit_side;
			return ;
		}
		i++;
	}
}

void	paraboloid_loop_shadow(t_ray r, t_scene *scene, t_hits *hits)
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
		hits->hit_min = hit;
		if (hits->hit_min > 0 && hits->hit_min < scene->distance_to_spot)
			return ;
		i++;
	}
}
