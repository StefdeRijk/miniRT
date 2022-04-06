/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/06 11:25:31 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/06 11:25:31 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vec/vec.h"

int	ray_in_right_dir(t_ray r, t_cylinder cylinder)
{
	if (r.origin.y > cylinder.height / 2 || r.origin.y < -(cylinder.height / 2))
	{
		if (r.origin.y * r.dir.y >= 0)
			return (0);
	}
	return (1);
}

float	hit_top_or_bottom(t_ray ray, t_cylinder cylinder)
{
	float	t_plane;
	t_vec3f	p1;

	t_plane = -((ray.origin.y - signf(ray.origin.y) * \
		(cylinder.height / 2)) / ray.dir.y);
	p1 = at(ray, t_plane);
	if (p1.x * p1.x + p1.z * p1.z <= cylinder.radius * cylinder.radius)
		return (t_plane);
	return (-1.0);
}

t_vec3f	cylinder_side_normal(t_vec3f hit_pos, t_cylinder cylinder)
{
	float		distance_to_cylinder_plane;
	t_vec3f		hit_pos_in_cylinder_plane;
	t_ray		along_cylinder;

	along_cylinder.origin = hit_pos;
	along_cylinder.dir = cylinder.dir_base.dir;
	distance_to_cylinder_plane = hit_plane(cylinder.dir_base.dir, \
		cylinder.dir_base.base.pos, along_cylinder);
	hit_pos_in_cylinder_plane = at(along_cylinder, distance_to_cylinder_plane);
	return (vec3f_unit(vec3f_sub(hit_pos_in_cylinder_plane, \
		cylinder.dir_base.base.pos)));
}
