#include "miniRT.h"

t_vec3f	get_sphere_norm_color(t_hits hit, t_ray r, \
	t_sphere *spheres, t_vec3f *norm_dir)
{
	t_sphere			sphere;

	sphere = spheres[hit.object_index];
	*norm_dir = get_normal_sphere(at(r, hit.hit_min), sphere.pos);
	return (sphere.color);
}

t_vec3f	get_plane_norm_color(t_hits hit, t_ray r, \
	t_plane *planes, t_vec3f *norm_dir)
{
	t_plane	plane;

	plane = planes[hit.object_index];
	*norm_dir = plane_normal(plane.dir, r.dir);
	return (plane.color);
}

t_vec3f	get_cylinder_norm_color(t_hits hit, t_ray r, \
	t_cylinder *cylinders, t_vec3f *norm_dir, int hit_side_cylinder)
{
	t_cylinder	cylinder;

	cylinder = cylinders[hit.object_index];
	if (hit_side_cylinder)
		*norm_dir = cylinder_side_norm(at(r, hit.hit_min), cylinder);
	else
		*norm_dir = plane_normal(cylinder.dir, r.dir);
	return (cylinder.color);
}
