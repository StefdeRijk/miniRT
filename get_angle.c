#include "miniRT.h"
#include <math.h>

t_angle	set_correct_angle(t_angle s_angle)
{
	if (s_angle.angle < 0)
		s_angle.angle = -M_PI - s_angle.angle;
	else
		s_angle.angle = M_PI - s_angle.angle;
	return (s_angle);
}

t_angle	get_angle_to(t_vec3f dir, t_vec3f to)
{
	t_angle	s_angle;
	t_vec3f	rot_plane;
	float	len_rot_plane;

	s_angle.angle = 0;
	s_angle.k = vec3f_init(0, 0, 0);
	if (vec3f_equal(dir, vec3f_mul(to, -1)))
	{
		s_angle.angle = M_PI;
		if (to.y == 0 && to.z == 0)
			s_angle.k = vec3f_unit(vec3f_cross(dir, vec3f_init(0, 1, 0)));
		else
			s_angle.k = vec3f_unit(vec3f_cross(dir, vec3f_init(1, 0, 0)));
	}
	else
	{
		rot_plane = vec3f_cross(dir, to);
		len_rot_plane = vec3f_len(rot_plane);
		s_angle.angle = asin(len_rot_plane);
		if (vec3f_dot(dir, to) < 0)
			s_angle = set_correct_angle(s_angle);
		s_angle.k = vec3f_unit(rot_plane);
	}
	return (s_angle);
}

t_angle	get_angle(t_vec3f dir)
{
	return (get_angle_to(dir, vec3f_init(0, 1, 0)));
}
