#include "miniRT.h"
#include <math.h>

t_vec3f	ft_rodrigues(t_vec3f v, t_vec3f k, float angle)
{
	t_vec3f	term_1;
	t_vec3f	term_2;
	t_vec3f	term_3;
	t_vec3f	rotated;

	term_1 = vec3f_mul(v, cos(angle));
	term_2 = vec3f_mul(vec3f_cross(k, v), sin(angle));
	term_3 = vec3f_mul(k, (vec3f_dot(k, v) * (1 - cos(angle))));
	rotated = vec3f_add(term_1, term_2);
	rotated = vec3f_add(rotated, term_3);
	return (rotated);
}

float	abc(float a, float b, float c, int *solved)
{
	float d;

	d = b * b - 4 * a * c;
	if (d < 0)
	{
		*solved = 0;
		return (0);
	}
	else
	{
		*solved = 1;
		return ((-b - sqrt(d)) / (2.0 * a));
	}
}

float signf(float a) {
	if (a < 0)
		return (-1.0);
	return (1.0);
}

t_ray rotate_ray(t_ray r, t_cylinder cylinder)
{
	t_ray rot_ray;
	t_vec3f	rotated_dir;
	t_vec3f	rotated_origin;
	t_vec3f	rotated_cylinder;
	t_vec3f	k;
	t_vec3f	rot_plane;
	t_vec3f	shifted_origin;
	float	len_rot_plane;
	float	angle;

	if (cylinder.dir.x == 0 && cylinder.dir.z == 0)
	{
		rotated_origin = r.origin;
		rotated_cylinder = cylinder.pos;
		rotated_dir = r.dir;
	}
	else
	{
	rot_plane = vec3f_cross(cylinder.dir, vec3f_init(0, 1, 0));
	len_rot_plane = vec3f_len(rot_plane);
	angle = asin(len_rot_plane);
	k = vec3f_unit(rot_plane);
	rotated_dir = ft_rodrigues(r.dir, k, angle);
	rotated_origin = ft_rodrigues(r.origin, k, angle);
	rotated_cylinder= ft_rodrigues(cylinder.pos, k, angle);
	}
	shifted_origin = vec3f_sub(rotated_origin, rotated_cylinder);
	rot_ray.dir = rotated_dir;
	rot_ray.origin = shifted_origin;
	return (rot_ray);
}
int	ray_in_right_dir(t_ray r, t_cylinder cylinder)
{
	if (r.origin.y > cylinder.height / 2 || r.origin.y < -(cylinder.height / 2))
	{
		if (r.origin.y * r.dir.y >= 0)
		{
			// printf("not right height and direction\n");
			return (0);
		}
	}
	return (1);
}

float hit_top_or_bottom(t_ray ray, t_cylinder cylinder)
{
	float	t_plane;
	t_vec3f p1;

	t_plane = - (ray.origin.y - signf(ray.origin.y) * (cylinder.height / 2)) / ray.dir.y;
	p1 = at(ray, t_plane);
	if (p1.x * p1.x + p1.z * p1.z <= cylinder.radius * cylinder.radius)
	{
		//printf("hit top or bottom: %f\n", t_plane);
		return (t_plane);
	}
	return (-1.0);
}

float hit_infinite_cylinder(t_ray r, t_cylinder cylinder)
{
	float	a;
	float	b;
	float	c;
	int		solved;
	float	t;

	if (r.dir.x == 0 && r.dir.z == 0)
		return (-1.0);
	r.dir.y = 0;
	r.origin.y = 0;
	a = vec3f_len_sq(r.dir);
	b = 2.0 * (vec3f_dot(r.origin, r.dir));
	c = vec3f_len_sq(r.origin) - (cylinder.radius * cylinder.radius);
	t = abc(a, b, c, &solved);
	if (!solved)
		return (-1.0);
	return (t);
}

float   hit_cylinder(t_cylinder cylinder, t_ray r, int *hit_side)
{
	float	t_plane;
	t_vec3f p2;
	t_ray	rot_ray;
	float	t;

	*hit_side = 0;
	rot_ray = rotate_ray(r, cylinder);
	//vec3f_print(rot_ray.dir);
	//vec3f_print(rot_ray.origin);
	if (!ray_in_right_dir(rot_ray, cylinder))
	{
		//printf("not in right dir\n");
		return (-1.0);
	}
	t_plane = hit_top_or_bottom(rot_ray, cylinder);
	t = hit_infinite_cylinder(rot_ray, cylinder);
	//printf("t: %f\n", t);
	if (t < 0)
	{
		//printf("no hit on infinite cylinder\n");
		return (-1.0);
	}
	p2 = at(rot_ray, t);
	//printf("p2.y: %f\n", p2.y);
	if (fabsf(p2.y) < cylinder.height / 2)
	{
		if (t_plane < 0 || t < t_plane)
		{
		//printf("hit cylinder\n");
			*hit_side = 1;
			return (t);
		}
	}
	if (t_plane > 0)
		return (t_plane);
	//printf("end of function\n");
	return (-1.0);
}
