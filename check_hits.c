/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_hits.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/06 11:25:30 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/06 11:25:30 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

float	get_hit_distance(t_object object, t_ray r, int *hit_side)
{
	float	hit_distance;

	if (object.base.type == PLANE)
		hit_distance = hit_plane(object.plane.dir_base.dir, \
			object.plane.dir_base.base.pos, r);
	else if (object.base.type == SPHERE)
		hit_distance = hit_sphere(object.sphere, r);
	else if (object.base.type == CYLINDER)
		hit_distance = hit_cylinder(object.cylinder, r, hit_side);
	else
		hit_distance = hit_paraboloid(object.paraboloid, r);
	return (hit_distance);
}

void	objects_loop(t_ray r, t_scene *scene, t_hits *hits, \
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
		hit = get_hit_distance(objects[i], r, &hit_side);
		if (distance_to_spot > 0 && hit > 0 && \
			hit < distance_to_spot)
		{
			hits->hit_min = 1;
			return ;
		}
		if (!distance_to_spot && \
			check_hit(hit, &hits->hit_min, &hits->object_index, i))
		{
			hits->hit_type = objects[i].base.type;
			hits->material = objects[i].base.material;
			hits->hit_side_cylinder = hit_side;
		}
		i++;
	}
}
