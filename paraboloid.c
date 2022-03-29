#include "miniRT.h"
#include <math.h>

int	ray_in_right_dir_paraboloid(t_ray r)
{
	if (r.origin.y < 0)
	{
		if (r.origin.y * r.dir.y >= 0)
			return (0);
	}
	return (1);
}

float	get_t_paraboloid(t_paraboloid paraboloid, t_ray r)
{
	float	a;
	float	b;
	float	c;
	float	solution;
	int		solved;

	a = powf(r.dir.x, 2) + powf(r.dir.z, 2);
	b = 2 * (r.origin.x * r.dir.x) + 2 * (r.origin.z * r.dir.z) - \
		(r.dir.y * paraboloid.curvature);
	c = powf(r.origin.x, 2) + powf(r.origin.z, 2) - \
		(r.origin.y * paraboloid.curvature);
	solution = abc(a, b, c, &solved);
	if (!solved)
		return (-1.0);
	return (solution);
}

int	inside_paraboloid(t_ray r, t_paraboloid paraboloid)
{
	if (powf(r.origin.x, 2) + \
		powf(r.origin.z, 2) - r.origin.y * paraboloid.curvature < 0)
		return (1);
	return (0);
}

float	hit_paraboloid(t_paraboloid paraboloid, t_ray r)
{
	t_ray	rot_r;
	float	t;

	rot_r = rotate_ray(r, paraboloid.dir_base.base.pos, \
		paraboloid.dir_base.dir);
	if (!ray_in_right_dir_paraboloid(rot_r))
		return (-1.0);
	if (inside_paraboloid(rot_r, paraboloid))
		return (-2.0);
	t = get_t_paraboloid(paraboloid, rot_r);
	return (t);
}

/*
 * the derivative of y = x^2 / c is 2 x / c, and when this is equal to 1, 
 * then you're at the height of the focal point. 
 * This is when x = c /2, and y = c / 4.
 * the norm dir is calculated by adding a y unit vector to the direction from 
 * the hit point to the focal point
 */

t_vec3f	get_paraboloid_normal(t_hits hit, t_ray r, t_scene *scene)
{
	t_ray			rot_r;
	t_vec3f			norm_dir;
	t_angle			angle;
	float			focal_point;
	t_paraboloid	paraboloid;

	paraboloid = (((t_object *)(scene->objects.data)) \
		[hit.object_index]).paraboloid;
	rot_r = rotate_ray(r, paraboloid.dir_base.base.pos, \
		paraboloid.dir_base.dir);
	focal_point = paraboloid.curvature / 4;
	norm_dir = vec3f_unit(vec3f_sub(vec3f_init(0, focal_point, 0), \
		at(rot_r, hit.hit_min)));
	norm_dir = vec3f_unit(vec3f_add(norm_dir, vec3f_init(0, 1, 0)));
	norm_dir = vec3f_mul(norm_dir, -1.);
	angle = get_angle_to(paraboloid.dir_base.dir, vec3f_init(0, 1, 0));
	norm_dir = ft_rodrigues(norm_dir, angle.k, -angle.angle);
	return (norm_dir);
}
