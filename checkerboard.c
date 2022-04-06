/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkerboard.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/06 11:25:30 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/06 11:25:30 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

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

	x_and_y = checkerboard_x_and_y(r, hit_min, cylinder.dir_base, \
		10. / cylinder.height);
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

	x_and_y = checkerboard_x_and_y(r, hit_min, paraboloid.dir_base, \
		10. / paraboloid.curvature);
	x_plus_y = (int)x_and_y.x + (int)x_and_y.y;
	return (checkerboard_make_squares(x_plus_y, \
		paraboloid.dir_base.base.color));
}
