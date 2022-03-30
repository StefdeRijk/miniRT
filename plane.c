#include "miniRT.h"
#include <math.h>

float	hit_plane(t_vec3f plane_dir, t_vec3f plane_pos, t_ray r)
{
	t_vec3f	p_min_l;
	float	dot_plane_orientation;
	float	dot_l_n;

	p_min_l = vec3f_sub(plane_pos, r.origin);
	dot_plane_orientation = vec3f_dot(p_min_l, plane_dir);
	dot_l_n = vec3f_dot(r.dir, plane_dir);
	return (dot_plane_orientation / dot_l_n);
}

t_vec3f	plane_normal_bump(t_vec3f pos_on_plane, t_plane plane, t_vec3f ray_dir)
{
	t_vec3f		normal;
	int			bump_x;
	int			bump_y;
	int			base_index;
	t_vec3f		bump;
	t_angle		angle;

	normal = plane_normal(plane.dir_base.dir, ray_dir);
	if (!BONUS || !plane.dir_base.base.bump_map.data)
		return (normal);
	bump_x = ((int)(fabsf(pos_on_plane.x) * \
		plane.dir_base.base.bump_map.width)) % \
			plane.dir_base.base.bump_map.width;
	bump_y = ((int)(fabsf(pos_on_plane.y) * \
		plane.dir_base.base.bump_map.height)) % \
			plane.dir_base.base.bump_map.height;
	base_index = bump_x * plane.dir_base.base.bump_map.bytes_per_pixel + \
		bump_y * plane.dir_base.base.bump_map.bytes_per_row;
	bump = read_bump(plane.dir_base.base.bump_map, base_index);
	angle = get_angle_to(vec3f_init(0, 0, -1), normal);
	bump = ft_rodrigues(bump, angle.k, angle.angle);
	if (pos_on_plane.x > 0) //cannot be the correct fix, sphere still broken
		bump.x *= -1;
	if (pos_on_plane.y > 0)
		bump.y *= -1;
	return (bump);
}

t_vec3f	plane_normal(t_vec3f plane_dir, t_vec3f ray_dir)
{
	float		which_side;
	t_vec3f		normal;

	which_side = vec3f_dot(plane_dir, ray_dir);
	if (which_side > 0.)
		normal = (vec3f_sub(vec3f_init(0, 0, 0), vec3f_unit(plane_dir)));
	else
		normal = (vec3f_unit(plane_dir));
	return (normal);
}
