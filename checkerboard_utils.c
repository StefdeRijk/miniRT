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

t_vec3f	checkerboard_x_and_y(t_ray r, float hit_min, \
	t_directed_base dir_base, float multiplier)
{
	t_angle	angle;
	t_vec3f	hit_point;
	t_vec3f	rotated_hit_point;

	hit_point = at(r, hit_min);
	hit_point = vec3f_sub(hit_point, dir_base.base.pos);
	angle = get_angle_to(dir_base.dir, vec3f_init(0, 1, 0));
	rotated_hit_point = ft_rodrigues(hit_point, angle.k, angle.angle);
	rotated_hit_point.x = get_x_angle(rotated_hit_point);
	rotated_hit_point.y *= multiplier;
	if (rotated_hit_point.y < 0)
		rotated_hit_point.y -= 1;
	return (rotated_hit_point);
}
