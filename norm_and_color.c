#include "miniRT.h"
#include <math.h>

t_vec3f	get_color_checkerboard_plane(t_plane plane, t_vec3f norm_dir, \
	t_ray r, float hit_min)
{
	t_angle	angle;
	t_vec3f	hit_point;
	t_vec3f	rotated_hit_point;
	int		x_plus_z;

	hit_point = at(r, hit_min);
	hit_point = vec3f_sub(hit_point, plane.pos);
	angle = get_angle(norm_dir);
	rotated_hit_point = ft_rodrigues(hit_point, angle.k, angle.angle);
	x_plus_z = (int)rotated_hit_point.x + (int)rotated_hit_point.z;
	if (abs(x_plus_z) % 2 > 0)
		return (vec3f_div(plane.color, 7.5));
	return (plane.color);
}

t_vec3f	get_color_checkerboard_sphere(t_sphere sphere, t_vec3f norm_dir)
{
	float	x_angle;
	float	y_angle;
	int		x_plus_y;

	x_angle = vec3f_dot(vec3f_unit(vec3f_init(norm_dir.x, 0, norm_dir.z)), \
		vec3f_init(1, 0, 0));
	x_angle = acos(x_angle);
	x_angle = x_angle * 4;
	y_angle = vec3f_dot(norm_dir, vec3f_init(0, 1, 0));
	y_angle = acos(y_angle);
	y_angle = y_angle * 4;
	x_plus_y = (int)x_angle + (int)y_angle;
	if (abs(x_plus_y) % 2 > 0)
		return (vec3f_div(sphere.color, 7.5));
	return (sphere.color);
}

t_vec3f	get_sphere_norm_color(t_hits hit, t_ray r, \
	t_sphere *spheres, t_vec3f *norm_dir)
{
	t_sphere			sphere;

	sphere = spheres[hit.object_index];
	*norm_dir = get_normal_sphere(at(r, hit.hit_min), sphere.pos);
	if (BONUS && sphere.material == CHECKER)
		return (get_color_checkerboard_sphere(sphere, *norm_dir));
	return (sphere.color);
}

t_vec3f	get_plane_norm_color(t_hits hit, t_ray r, \
	t_plane *planes, t_vec3f *norm_dir)
{
	t_plane	plane;

	plane = planes[hit.object_index];
	*norm_dir = plane_normal(plane.dir, r.dir);
	if (BONUS && plane.material == CHECKER)
		return (get_color_checkerboard_plane(plane, *norm_dir, r, hit.hit_min));
	return (plane.color);
}

t_vec3f	get_cylinder_norm_color(t_hits hit, t_ray r, \
	t_cylinder *cylinders, t_vec3f *norm_dir)
{
	t_cylinder	cylinder;

	cylinder = cylinders[hit.object_index];
	if (hit.hit_side_cylinder)
		*norm_dir = cylinder_side_norm(at(r, hit.hit_min), cylinder);
	else
		*norm_dir = plane_normal(cylinder.dir, r.dir);
	return (cylinder.color);
}
