#include "miniRT.h"
#include <math.h>

t_vec3f	get_rotated_hit_point(t_plane plane, t_ray r, float hit_min)
{
	t_vec3f	hit_point;
	t_vec3f	norm_dir;
	t_angle	angle;

	norm_dir = plane_normal(plane.dir_base.dir, r.dir);
	hit_point = at(r, hit_min);
	hit_point = vec3f_sub(hit_point, plane.dir_base.base.pos);
	angle = get_angle(norm_dir);
	return (ft_rodrigues(hit_point, angle.k, angle.angle));
}

t_vec3f	mix_diffuse_and_smooth(t_hits hit, t_ray r,
		t_scene *scene, t_vec3f *norm_dir, t_vec3f color, t_vec3f color2)
{
	t_vec3f	color1;
	float	ratio;

	color1 = get_color_mirror(*norm_dir, r, hit.hit_min, scene);
	ratio = vec3f_len_sq(color) / 3.;
	color = vec3f_mul(color1, ratio);
	color = vec3f_add(color, vec3f_mul(color2, 1 - ratio));
	return (color);
}

t_vec3f	get_sphere_norm_color(t_hits hit, t_ray r, t_vec3f *norm_dir, t_scene *scene)
{
	t_sphere	sphere;
	t_vec3f		color;
	t_vec3f		sphere_norm;

	sphere = (((t_object *)(scene->objects.data))[hit.object_index]).sphere;
	color = sphere.base.color;
	*norm_dir = get_normal_bump_sphere(at(r, hit.hit_min), sphere.base.pos, sphere);
	sphere_norm = get_normal_sphere(at(r, hit.hit_min), sphere.base.pos);
	if (sphere.base.texture.data)
		color = get_sphere_texture(sphere, r, hit);
	if (BONUS && sphere.base.material == CHECKER)
		color = get_color_checkerboard_sphere(sphere_norm, color);
	if (BONUS && sphere.base.material == MIRROR)
	{
		if (sphere.base.texture.data)
			color = mix_diffuse_and_smooth(hit, r, scene, norm_dir, color, sphere.base.color);
		else
			color = get_color_mirror(*norm_dir, r, hit.hit_min, scene);
	}
	return (color);
}

t_vec3f	get_plane_norm_color(t_hits hit, t_ray r, \
		t_scene *scene, t_vec3f *norm_dir)
{
	t_plane	plane;
	t_vec3f	rotated_hit_point;
	t_vec3f	plane_pos;
	t_vec3f	color;

	plane = ((t_plane *)(scene->objects.data))[hit.object_index];
	color = plane.dir_base.base.color;
	rotated_hit_point = get_rotated_hit_point(plane, r, hit.hit_min);
	plane_pos.x = fabsf(rotated_hit_point.x);
	plane_pos.y = fabsf(rotated_hit_point.z);
	*norm_dir = plane_normal_bump(plane_pos, plane, r.dir);
	if (plane.dir_base.base.texture.data)
		color = get_plane_texture(plane, plane_pos);
	if (BONUS && plane.dir_base.base.material == CHECKER)
		color = get_color_checkerboard_plane(plane, r, hit.hit_min, color);
	if (BONUS && plane.dir_base.base.material == MIRROR)
	{
		if (plane.dir_base.base.texture.data)
			color = mix_diffuse_and_smooth(hit, r, scene, norm_dir, color, plane.dir_base.base.color);
		else
			color = get_color_mirror(*norm_dir, r, hit.hit_min, scene);
	}
	return (color);
}

t_vec3f	get_cylinder_norm_color(t_hits hit, t_ray r, t_vec3f *norm_dir, t_scene *scene)
{
	t_cylinder	cylinder;
	t_vec3f		color;

	cylinder = (((t_object *)(scene->objects.data))[hit.object_index]).cylinder;
	color = cylinder.dir_base.base.color;
	if (hit.hit_side_cylinder)
		*norm_dir = cylinder_side_norm(at(r, hit.hit_min), cylinder);
	else
		*norm_dir = plane_normal(cylinder.dir_base.dir, r.dir);
	if (BONUS && cylinder.dir_base.base.material == CHECKER)
		color = get_color_checkerboard_cylinder(cylinder, r, hit.hit_min, \
			hit.hit_side_cylinder);
	if (BONUS && cylinder.dir_base.base.material == MIRROR)
			color = get_color_mirror(*norm_dir, r, hit.hit_min, scene);
	return (color);
}

t_vec3f	get_paraboloid_norm_color(t_hits hit, t_ray r, t_vec3f *norm_dir, t_scene *scene)
{
	t_paraboloid	paraboloid;
	t_vec3f			color;

	paraboloid = (((t_object *)(scene->objects.data))[hit.object_index]).paraboloid;
	color = paraboloid.dir_base.base.color;
	*norm_dir = paraboloid_normal(paraboloid, r, hit);
	if (BONUS && paraboloid.dir_base.base.material == CHECKER)
		color = get_color_checkerboard_paraboloid(paraboloid, r, \
			hit.hit_min);
	if (BONUS && paraboloid.dir_base.base.material == MIRROR)
			color = get_color_mirror(*norm_dir, r, hit.hit_min, scene);
	return (color);
}
