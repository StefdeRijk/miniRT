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

void	objects_loop(t_ray r, t_scene *scene, t_hits *hits)
{
	int			i;
	int			hit_side;
	float		hit;
	t_object	*objects;

	i = 0;
	objects = scene->objects.data;
	while (i < scene->objects.len)
	{
		if (objects->base.type == PLANE)
			hit = hit_plane(objects[i].plane.dir_base.dir, objects[i].plane.dir_base.base.pos, r);
		else if (objects->base.type == SPHERE)
			hit = hit_sphere(objects[i].sphere, r);
		else if (objects->base.type == CYLINDER)
			hit = hit_cylinder(objects[i].cylinder, r, &hit_side);
		else if (objects->base.type == PARABOLOID)
			hit = hit_paraboloid(objects[i].paraboloid, r);
		if (check_hit(hit, &hits->hit_min, &hits->object_index, i))
		{
			hits->hit_type = objects[i].base.type;
			hits->material = objects[i].base.material;
			if (objects->base.type == CYLINDER)
				hits->hit_side_cylinder = hit_side;
		}
		i++;
	}
}

void	objects_loop_shadow(t_ray r, t_scene *scene, t_hits *hits, \
	float distance_to_spot)
{
	int			i;
	int			hit_side;
	float		hit;
	t_object	*objects;

	i = 0;
	objects = scene->objects.data;
	while (i < scene->objects.len)
	{
		if (objects->base.type == PLANE)
			hit = hit_plane(objects[i].plane.dir_base.dir, objects[i].plane.dir_base.base.pos, r);
		else if (objects->base.type == SPHERE)
			hit = hit_sphere(objects[i].sphere, r);
		else if (objects->base.type == CYLINDER)
			hit = hit_cylinder(objects[i].cylinder, r, &hit_side);
		else if (objects->base.type == PARABOLOID)
			hit = hit_paraboloid(objects[i].paraboloid, r);
		hits->hit_min = hit;
		if (hits->hit_min > 0 && hits->hit_min < distance_to_spot)
			return ;
		i++;
	}
}

// void	sphere_loop(t_ray r, t_scene *scene, t_hits *hits)
// {
// 	int			i;
// 	t_sphere	sphere;
// 	t_sphere	*spheres;
// 	float		hit;

// 	spheres = scene->spheres.data;
// 	i = 0;
// 	while (i < scene->spheres.len)
// 	{
// 		sphere = spheres[i];
// 		hit = hit_sphere(sphere, r);
// 		if (check_hit(hit, &hits->hit_min, &hits->object_index, i))
// 		{
// 			hits->hit_type = SPHERE;
// 			hits->material = sphere.base.material;
// 		}
// 		i++;
// 	}
// }

// void	cylinder_loop(t_ray r, t_scene *scene, t_hits *hits)
// {
// 	int			i;
// 	t_cylinder	cylinder;
// 	t_cylinder	*cylinders;
// 	float		hit;
// 	int			hit_side;

// 	hit_side = 0;
// 	cylinders = scene->cylinders.data;
// 	i = 0;
// 	while (i < scene->cylinders.len)
// 	{
// 		cylinder = cylinders[i];
// 		hit = hit_cylinder(cylinder, r, &hit_side);
// 		if (check_hit(hit, &hits->hit_min, &hits->object_index, i))
// 		{
// 			hits->hit_type = CYLINDER;
// 			hits->hit_side_cylinder = hit_side;
// 			hits->material = cylinder.dir_base.base.material;
// 		}
// 		i++;
// 	}
// }

// void	paraboloid_loop(t_ray r, t_scene *scene, t_hits *hits)
// {
// 	int				i;
// 	t_paraboloid	paraboloid;
// 	t_paraboloid	*paraboloids;
// 	float			hit;

// 	paraboloids = scene->paraboloids.data;
// 	i = 0;
// 	while (i < scene->paraboloids.len)
// 	{
// 		paraboloid = paraboloids[i];
// 		hit = hit_paraboloid(paraboloid, r);
// 		if (check_hit(hit, &hits->hit_min, &hits->object_index, i))
// 		{
// 			hits->hit_type = PARABOLOID;
// 			hits->material = paraboloid.dir_base.base.material;
// 		}
// 		i++;
// 	}
// }
