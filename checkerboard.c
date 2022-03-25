#include "miniRT.h"
#include <math.h>

t_vec3f	checkerboard_make_squares(int x_plus_y, t_vec3f color)
{
	if (abs(x_plus_y) % 2 > 0)
		return (vec3f_div(color, 7.5));
	return (color);
}

float	get_x_angle(t_vec3f rotated_hit_point)
{
	t_vec3f	unit_rotated_hit_point;
	float	x_angle;

	unit_rotated_hit_point = vec3f_unit(rotated_hit_point);
	x_angle = vec3f_dot(vec3f_unit(vec3f_init(unit_rotated_hit_point.x, 0, \
		unit_rotated_hit_point.z)), vec3f_init(1, 0, 0));
	x_angle = acos(x_angle);
	if (rotated_hit_point.z > 0)
		x_angle = x_angle / M_PI * 4.999;
	else
		x_angle = x_angle / M_PI * 4.999 + 1;
	return (x_angle);
}

t_vec3f	checkerboard_x_and_y(t_ray r, float hit_min, t_directed_base dir_base, float multiplier)
{
	t_angle	angle;
	t_vec3f	hit_point;
	t_vec3f	rotated_hit_point;

	hit_point = at(r, hit_min);
	hit_point = vec3f_sub(hit_point, dir_base.base.pos);
	angle = get_angle(dir_base.dir);
	rotated_hit_point = ft_rodrigues(hit_point, angle.k, angle.angle);
	rotated_hit_point.x = get_x_angle(rotated_hit_point);
	rotated_hit_point.y *= multiplier;
	if (rotated_hit_point.y < 0)
		rotated_hit_point.y -= 1;
	return (rotated_hit_point);
}

t_vec3f	get_color_checkerboard_plane(t_plane plane, t_ray r,
	float hit_min, t_vec3f color)
{
	t_vec3f	rotated_hit_point;
	int		x_plus_z;

	rotated_hit_point = get_rotated_hit_point(plane, r, hit_min);
	x_plus_z = (int)rotated_hit_point.x + (int)rotated_hit_point.z;
	return (checkerboard_make_squares(x_plus_z, color));
}

t_vec3f	get_color_checkerboard_sphere(t_vec3f norm_dir, t_vec3f color)
{
	float	x_angle;
	float	y_angle;
	int		x_plus_y;

	get_sphere_angles(norm_dir, &x_angle, &y_angle);
	x_angle = x_angle * 5;
	y_angle = y_angle * 10;
	x_plus_y = (int)x_angle + (int)y_angle;
	return (checkerboard_make_squares(x_plus_y, color));
}


t_vec3f	get_color_checkerboard_cylinder(t_cylinder cylinder, t_ray r, \
	float hit_min, int hit_side_cylinder)
{
	int		x_plus_y;
	t_vec3f	x_and_y;

	x_and_y = checkerboard_x_and_y(r, hit_min, cylinder.dir_base, 10. / cylinder.height);
	if (hit_side_cylinder)
		x_plus_y = (int)x_and_y.x + (int)x_and_y.y;
	else
		x_plus_y = (int)x_and_y.x;
	return (checkerboard_make_squares(x_plus_y, cylinder.dir_base.base.color));
}

t_vec3f	get_color_checkerboard_paraboloid(t_paraboloid paraboloid, t_ray r, \
	float hit_min)
{
	int		x_plus_y;
	t_vec3f	x_and_y;

	x_and_y = checkerboard_x_and_y(r, hit_min, paraboloid.dir_base, 10. / paraboloid.curvature);
	x_plus_y = (int)x_and_y.x + (int)x_and_y.y;
	return (checkerboard_make_squares(x_plus_y, paraboloid.dir_base.base.color));
}
