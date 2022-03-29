#include "miniRT.h"
#include <math.h>

t_vec3f	get_sphere_norm(t_hits hit, t_ray r, t_scene *scene)
{
	t_sphere	sphere;

	sphere = (((t_object *)(scene->objects.data))[hit.object_index]).sphere;
	return (get_normal_bump_sphere(at(r, hit.hit_min), sphere.base.pos, sphere));
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

t_vec3f	get_plane_norm(t_hits hit, t_ray r, t_scene *scene)
{
	t_plane	plane;
	t_vec3f	plane_pos;

	plane = (((t_object *)(scene->objects.data))[hit.object_index]).plane;
	plane_pos = get_plane_pos(hit, r, plane);
	return (plane_normal_bump(plane_pos, plane, r.dir));
}

t_vec3f	get_cylinder_norm(t_hits hit, t_ray r, t_scene *scene)
{
	t_cylinder	cylinder;
	cylinder = (((t_object *)(scene->objects.data))[hit.object_index]).cylinder;
	if (hit.hit_side_cylinder)
		return (cylinder_side_norm(at(r, hit.hit_min), cylinder));
	else
		return (plane_normal(cylinder.dir_base.dir, r.dir));
}

