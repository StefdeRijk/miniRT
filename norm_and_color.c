#include "miniRT.h"

void	get_sphere_norm_color(t_hits hit, t_ray r, t_sphere *spheres, t_vec3f *norm_dir, t_vec3f *object_color)
{
	t_sphere			sphere;

	sphere = spheres[hit.object_index];
	*norm_dir = get_normal_sphere(at(r, hit.hit_min), sphere.pos);
	*object_color = sphere.color;
}

void	get_plane_norm_color(t_hits hit, t_ray r, t_plane *planes, t_vec3f *norm_dir, t_vec3f *object_color)
{
	t_plane	plane;

	plane = planes[hit.object_index];
	*norm_dir = plane_normal(plane.dir, r.dir);
	*object_color = plane.color;
}

void	get_cylinder_norm_color(t_hits hit, t_ray r, t_cylinder *cylinders, t_vec3f *norm_dir, t_vec3f *object_color, int hit_side_cylinder)
{
	t_cylinder	cylinder;

	cylinder = cylinders[hit.object_index];
	if (hit_side_cylinder)
		*norm_dir = cylinder_side_norm(at(r, hit.hit_min), cylinder);
	else
		*norm_dir = plane_normal(cylinder.dir, r.dir);
	*object_color = cylinder.color;
}
