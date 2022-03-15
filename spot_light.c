#include "miniRT.h"
#include <math.h>

#define SPOT_BRIGHTNESS 70

int	get_hit_shadow(t_light light, t_ray r, t_vec3f pos, t_scene *scene)
{
	t_hits	hit;
	float	distance_to_spot;

	hit.hit_min = 0.;
	hit.hit_side_cylinder = 0;
	distance_to_spot = vec3f_len(vec3f_sub(light.pos, pos));
	sphere_loop_shadow(r, scene, &hit, distance_to_spot);
	if (hit.hit_min > 0 && hit.hit_min < distance_to_spot)
		return (1);
	plane_loop_shadow(r, scene, &hit, distance_to_spot);
	if (hit.hit_min > 0 && hit.hit_min < distance_to_spot)
		return (1);
	cylinder_loop_shadow(r, scene, &hit, distance_to_spot);
	if (hit.hit_min > 0 && hit.hit_min < distance_to_spot)
		return (1);
	if (BONUS)
	{
		paraboloid_loop_shadow(r, scene, &hit, distance_to_spot);
		if (hit.hit_min > 0 && hit.hit_min < distance_to_spot)
			return (1);
	}
	return (0);
}

int	in_shadow(t_vec3f pos, t_light light, t_ray r, t_scene *scene)
{
	t_ray	to_spot;
	t_vec3f	reverse_r_dir;
	t_vec3f	offset;
	t_vec3f	spot_dir;

	spot_dir = vec3f_unit(vec3f_sub(light.pos, pos));
	to_spot.dir = spot_dir;
	reverse_r_dir = vec3f_sub(vec3f_init(0, 0, 0), r.dir);
	offset = vec3f_mul(reverse_r_dir, 0.0001);
	to_spot.origin = vec3f_add(pos, offset);
	if (get_hit_shadow(light, to_spot, pos, scene))
		return (1);
	return (0);
}

t_vec3f	spot_light_specular(t_vec3f normal, t_light light, t_old_new_ray rays,
		t_scene *scene)
{
	t_vec3f		spot_dir;
	t_vec3f		spot_color_specular;
	float		in_product_specular;
	float		alpha;
	t_vec3f		reflected_spot;

	alpha = 20;
	spot_dir = vec3f_unit(vec3f_sub(light.pos, rays.n.origin));
	reflected_spot = f_reflection(spot_dir, normal);
	reflected_spot = vec3f_unit(reflected_spot);
	in_product_specular = vec3f_dot(reflected_spot, vec3f_unit(rays.o.dir));
	if (in_product_specular < 0 || in_shadow(rays.n.origin,
			light, rays.o, scene))
		return (vec3f_init(0, 0, 0));
	spot_color_specular = vec3f_mul(light.color, \
		((light.brightness * powf(in_product_specular, alpha))
				/ vec3f_len_sq(spot_dir)) * SPOT_BRIGHTNESS);
	return (spot_color_specular);
}

t_vec3f	get_spot_color(t_vec3f spot_unit, t_old_new_ray rays, t_vec3f normal, t_light light,
		t_scene *scene)
{
	float	distance_sq;
	t_vec3f	spot_color_diffuse;
	float	in_product;

	distance_sq = vec3f_len_sq(spot_unit);
	spot_unit = vec3f_unit(spot_unit);
	in_product = vec3f_dot(spot_unit, normal);
	if (in_product < 0
		|| in_shadow(rays.n.origin, light, rays.o, scene))
		return (vec3f_init(0, 0, 0));
	spot_color_diffuse = vec3f_mul(light.color, \
		((light.brightness * in_product) / distance_sq) \
		* SPOT_BRIGHTNESS);
	return (spot_color_diffuse);
}

t_vec3f	spot_light(t_old_new_ray rays, t_vec3f normal, t_light light,
	t_scene *scene)
{
	t_vec3f	spot_dir;
	t_vec3f	spot_color_diffuse;
	t_vec3f	new_spot_pos;
	int		i;
	t_ray	norm_r;
	float	dist_to_plane;
	t_plane	plane;

	i = 0;
	spot_dir = vec3f_sub(light.pos, rays.n.origin);
	spot_color_diffuse = get_spot_color(spot_dir, rays, normal, light, scene);
	while (i < scene->planes.len && BONUS)
	{
		plane = ((t_plane *)(scene->planes.data))[i];
		if (plane.material != MIRROR)
		{
			i++;
			continue ;
		}
		norm_r.origin = light.pos;
		norm_r.dir = vec3f_mul(normal, -1.);
		dist_to_plane = hit_plane(plane.dir, plane.pos, norm_r);
		new_spot_pos = vec3f_sub(light.pos, vec3f_mul(normal, 2 * dist_to_plane));
		spot_dir = vec3f_sub(new_spot_pos, rays.n.origin);
		spot_color_diffuse = vec3f_add(spot_color_diffuse, \
			get_spot_color(spot_dir, rays, normal, light, scene));
		i++;
	}
	// vec3f_print(spot_color_diffuse);
	return (spot_color_diffuse);
}
