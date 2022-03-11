#include "miniRT.h"
#include <math.h>

t_vec3f	get_color_checkerboard_paraboloid(t_paraboloid paraboloid, t_ray r, \
			float hit_min)
{
	t_angle	angle;
	t_vec3f	hit_point;
	t_vec3f	rotated_hit_point;
	t_vec3f	unit_rotated_hit_point;
	float	x_angle;
	int		x_plus_y;

	hit_point = at(r, hit_min);
	hit_point = vec3f_sub(hit_point, paraboloid.pos);
	angle = get_angle(paraboloid.dir);
	rotated_hit_point = ft_rodrigues(hit_point, angle.k, angle.angle);
	unit_rotated_hit_point = vec3f_unit(rotated_hit_point);
	x_angle = vec3f_dot(vec3f_unit(vec3f_init(unit_rotated_hit_point.x, 0, \
		unit_rotated_hit_point.z)), vec3f_init(1, 0, 0));
	x_angle = acos(x_angle);
	if (rotated_hit_point.z > 0)
		x_angle = x_angle / M_PI * 4.999;
	else
		x_angle = x_angle / M_PI * 4.999 + 1;
	rotated_hit_point.y = rotated_hit_point.y / paraboloid.curvature * 10;
	if (rotated_hit_point.y < 0)
		rotated_hit_point.y -= 1;
	x_plus_y = (int)x_angle + (int)rotated_hit_point.y;
	if (abs(x_plus_y) % 2 > 0)
		return (vec3f_div(paraboloid.color, 7.5));
	return (paraboloid.color);
}

t_vec3f get_rotated_hit_point(t_plane plane, t_ray r, float hit_min)
{
	t_vec3f	hit_point;
	t_vec3f norm_dir;
	t_angle	angle;

	norm_dir = plane_normal(plane.dir, r.dir);
	hit_point = at(r, hit_min);
	hit_point = vec3f_sub(hit_point, plane.pos);
	angle = get_angle(norm_dir);
	return (ft_rodrigues(hit_point, angle.k, angle.angle));
}

t_vec3f	get_color_checkerboard_plane(t_plane plane, t_ray r, float hit_min)
{
	t_vec3f	rotated_hit_point;
	int		x_plus_z;

	rotated_hit_point = get_rotated_hit_point(plane, r, hit_min);
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
	if (norm_dir.z > 0)
		x_angle = x_angle / M_PI * 5;
	else
		x_angle = x_angle / M_PI * 5 + 1;
	y_angle = vec3f_dot(norm_dir, vec3f_init(0, 1, 0));
	y_angle = acos(y_angle);
	y_angle = y_angle / M_PI * 10;
	x_plus_y = (int)x_angle + (int)y_angle;
	if (abs(x_plus_y) % 2 > 0)
		return (vec3f_div(sphere.color, 7.5));
	return (sphere.color);
}

t_vec3f	get_color_checkerboard_cylinder(t_cylinder cylinder, t_ray r, \
	float hit_min, int hit_side_cylinder)
{
	t_angle	angle;
	t_vec3f	hit_point;
	t_vec3f	rotated_hit_point;
	t_vec3f	unit_rotated_hit_point;
	float	x_angle;
	int		x_plus_y;

	hit_point = at(r, hit_min);
	hit_point = vec3f_sub(hit_point, cylinder.pos);
	angle = get_angle(cylinder.dir);
	rotated_hit_point = ft_rodrigues(hit_point, angle.k, angle.angle);
	unit_rotated_hit_point = vec3f_unit(rotated_hit_point);
	x_angle = vec3f_dot(vec3f_unit(vec3f_init(unit_rotated_hit_point.x, 0, \
		unit_rotated_hit_point.z)), vec3f_init(1, 0, 0));
	x_angle = acos(x_angle);
	if (rotated_hit_point.z > 0)
		x_angle = x_angle / M_PI * 5;
	else
		x_angle = x_angle / M_PI * 5 + 1;
	rotated_hit_point.y = rotated_hit_point.y / cylinder.height * 10;
	if (rotated_hit_point.y < 0)
		rotated_hit_point.y -= 1;
	if (hit_side_cylinder)
		x_plus_y = (int)x_angle + (int)rotated_hit_point.y;
	else
		x_plus_y = (int)x_angle;
	if (abs(x_plus_y) % 2 > 0)
		return (vec3f_div(cylinder.color, 7.5));
	return (cylinder.color);
}

t_vec3f	get_sphere_norm_color(t_hits hit, t_ray r, \
	t_sphere *spheres, t_vec3f *norm_dir)
{
	t_sphere			sphere;

	sphere = spheres[hit.object_index];
	*norm_dir = get_normal_bump_sphere(at(r, hit.hit_min), sphere.pos, spere);
	if (BONUS && sphere.material == CHECKER)
		return (get_color_checkerboard_sphere(sphere, *norm_dir));
	return (sphere.color);
}

t_vec3f	get_plane_norm_color(t_hits hit, t_ray r, \
	t_plane *planes, t_vec3f *norm_dir)
{
	t_plane	plane;
	t_vec3f	rotated_hit_point;
	t_vec3f	plane_pos;

	plane = planes[hit.object_index];
	rotated_hit_point = get_rotated_hit_point(plane, r, hit.hit_min);
	plane_pos.x = fabsf(rotated_hit_point.x);
	plane_pos.y = fabsf(rotated_hit_point.z);
	*norm_dir = plane_normal_bump(plane_pos, plane, r.dir);
	if (BONUS && plane.material == CHECKER)
		return (get_color_checkerboard_plane(plane, r, hit.hit_min));
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
	if (BONUS && cylinder.material == CHECKER)
		return (get_color_checkerboard_cylinder(cylinder, r, hit.hit_min, \
			hit.hit_side_cylinder));
	return (cylinder.color);
}

t_vec3f	get_paraboloid_norm_color(t_hits hit, t_ray r, \
	t_paraboloid *paraboloids, t_vec3f *norm_dir)
{
	t_paraboloid	paraboloid;

	paraboloid = paraboloids[hit.object_index];
	*norm_dir = paraboloid_normal(paraboloid, r, hit);
	if (BONUS && paraboloid.material == CHECKER)
		return (get_color_checkerboard_paraboloid(paraboloid, r, \
			hit.hit_min));
	return (paraboloid.color);
}
