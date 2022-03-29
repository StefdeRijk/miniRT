#include "miniRT.h"
#include <math.h>

t_vec3f	get_sphere_normal(t_hits hit, t_ray r, t_scene *scene)
{
	t_sphere	sphere;
	t_vec3f		normal;
	int			index;

	sphere = (((t_object *)(scene->objects.data))[hit.object_index]).sphere;
	normal = get_normal_sphere(at(r, hit.hit_min), sphere.base.pos);
	if (!BONUS || !sphere.base.bump_map.data)
		return (normal);
	index = get_sphere_base_index(sphere.base.bump_map, normal);
	return (read_bump(sphere.base.bump_map, index, normal));
}

t_vec3f	get_plane_pos(t_hits hit, t_ray r, t_plane plane)
{
	t_vec3f	plane_pos;
	t_vec3f	rotated_hit_point;

	rotated_hit_point = get_rotated_hit_point(plane, r, hit.hit_min);
	plane_pos.x = fabsf(rotated_hit_point.x);
	plane_pos.y = fabsf(rotated_hit_point.z);
	return (plane_pos);
}

t_vec3f	get_plane_normal(t_hits hit, t_ray r, t_scene *scene)
{
	t_plane	plane;
	t_vec3f	plane_pos;

	plane = (((t_object *)(scene->objects.data))[hit.object_index]).plane;
	plane_pos = get_plane_pos(hit, r, plane);
	return (plane_normal_bump(plane_pos, plane, r.dir));
}

t_vec3f	get_cylinder_normal(t_hits hit, t_ray r, t_scene *scene)
{
	t_cylinder	cylinder;
	cylinder = (((t_object *)(scene->objects.data))[hit.object_index]).cylinder;
	if (hit.hit_side_cylinder)
		return (cylinder_side_normal(at(r, hit.hit_min), cylinder));
	else
		return (plane_normal(cylinder.dir_base.dir, r.dir));
}

