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

	i = -1;
	objects = scene->objects.data;
	while (i++ < scene->objects.len)
	{
		if (objects[i].base.type == PLANE)
			hit = hit_plane(objects[i].plane.dir_base.dir, \
				objects[i].plane.dir_base.base.pos, r);
		else if (objects[i].base.type == SPHERE)
			hit = hit_sphere(objects[i].sphere, r);
		else if (objects[i].base.type == CYLINDER)
			hit = hit_cylinder(objects[i].cylinder, r, &hit_side);
		else if (objects[i].base.type == PARABOLOID)
			hit = hit_paraboloid(objects[i].paraboloid, r);
		if (check_hit(hit, &hits->hit_min, &hits->object_index, i))
		{
			hits->hit_type = objects[i].base.type;
			hits->material = objects[i].base.material;
			hits->hit_side_cylinder = hit_side;
		}
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
		if (objects[i].base.type == PLANE)
			hit = hit_plane(objects[i].plane.dir_base.dir, \
				objects[i].plane.dir_base.base.pos, r);
		else if (objects[i].base.type == SPHERE)
			hit = hit_sphere(objects[i].sphere, r);
		else if (objects[i].base.type == CYLINDER)
			hit = hit_cylinder(objects[i].cylinder, r, &hit_side);
		else if (objects[i].base.type == PARABOLOID)
			hit = hit_paraboloid(objects[i].paraboloid, r);
		hits->hit_min = hit;
		if (hits->hit_min > 0 && hits->hit_min < distance_to_spot)
			return ;
		i++;
	}
}
