#include "miniRT.h"
#include <math.h>

t_vec3f	mix_diffuse_and_smooth(t_hits hit, t_ray r,
		t_scene *scene, t_vec3f norm_dir, t_vec3f color)
{
	t_vec3f	color1;
	float	ratio;
	t_vec3f	color2;

	color2 = (((t_object *)(scene->objects.data))[hit.object_index]).base.color;
	color1 = get_color_mirror(norm_dir, r, hit.hit_min, scene);
	ratio = vec3f_len_sq(color) / 3.;
	color = vec3f_mul(color1, ratio);
	color = vec3f_add(color, vec3f_mul(color2, 1 - ratio));
	return (color);
}

t_vec3f	get_sphere_norm(t_hits hit, t_ray r, t_scene *scene)
{
	t_sphere	sphere;

	sphere = (((t_object *)(scene->objects.data))[hit.object_index]).sphere;
	return (get_normal_bump_sphere(at(r, hit.hit_min), sphere.base.pos, sphere));
}

t_vec3f	get_sphere_color(t_hits hit, t_ray r, t_vec3f norm_dir, t_scene *scene)
{
	t_sphere	sphere;
	t_vec3f		color;
	t_vec3f		sphere_norm;

	sphere = (((t_object *)(scene->objects.data))[hit.object_index]).sphere;
	color = sphere.base.color;
	sphere_norm = get_normal_sphere(at(r, hit.hit_min), sphere.base.pos);
	if (sphere.base.texture.data)
		color = get_sphere_texture(sphere, r, hit);
	if (BONUS && sphere.base.material == CHECKER)
		color = get_color_checkerboard_sphere(sphere_norm, color);
	if (BONUS && sphere.base.material == MIRROR)
	{
		if (sphere.base.texture.data)
			color = mix_diffuse_and_smooth(hit, r, scene, norm_dir, color);
		else
			color = get_color_mirror(norm_dir, r, hit.hit_min, scene);
	}
	return (color);
}

t_vec3f	get_plane_pos(t_hits hit, t_ray r, t_plane plane)
{
	t_vec3f	plane_pos;
	t_vec3f	rotated_hit_point;

	rotated_hit_point = get_rotated_hit_point(plane, r, hit.hit_min);
	plane_pos.x = fabsf(rotated_hit_point.x);
	plane_pos.y = fabsf(rotated_hit_point.z);
	return (plane_pos);
}

t_vec3f	get_plane_norm(t_hits hit, t_ray r, t_scene *scene)
{
	t_plane	plane;
	t_vec3f	plane_pos;

	plane = (((t_object *)(scene->objects.data))[hit.object_index]).plane;
	plane_pos = get_plane_pos(hit, r, plane);
	return (plane_normal_bump(plane_pos, plane, r.dir));
}

t_vec3f	get_plane_color(t_hits hit, t_ray r, \
		t_vec3f norm_dir, t_scene *scene)
{
	t_plane	plane;
	t_vec3f	plane_pos;
	t_vec3f	color;

	plane = (((t_object *)(scene->objects.data))[hit.object_index]).plane;
	plane_pos = get_plane_pos(hit, r, plane);
	color = plane.dir_base.base.color;
	if (plane.dir_base.base.texture.data)
		color = get_plane_texture(plane, plane_pos);
	if (BONUS && plane.dir_base.base.material == CHECKER)
		color = get_color_checkerboard_plane(plane, r, hit.hit_min, color);
	if (BONUS && plane.dir_base.base.material == MIRROR)
	{
		if (plane.dir_base.base.texture.data)
			color = mix_diffuse_and_smooth(hit, r, scene, norm_dir, color);
		else
			color = get_color_mirror(norm_dir, r, hit.hit_min, scene);
	}
	return (color);
}

t_vec3f	get_cylinder_norm(t_hits hit, t_ray r, t_scene *scene)
{
	t_cylinder	cylinder;
	cylinder = (((t_object *)(scene->objects.data))[hit.object_index]).cylinder;
	if (hit.hit_side_cylinder)
		return (cylinder_side_norm(at(r, hit.hit_min), cylinder));
	else
		return (plane_normal(cylinder.dir_base.dir, r.dir));
}

t_vec3f	get_cylinder_color(t_hits hit, t_ray r, t_vec3f norm_dir, t_scene *scene)
{
	t_cylinder	cylinder;
	t_vec3f		color;

	cylinder = (((t_object *)(scene->objects.data))[hit.object_index]).cylinder;
	color = cylinder.dir_base.base.color;
	if (BONUS && cylinder.dir_base.base.material == CHECKER)
		color = get_color_checkerboard_cylinder(cylinder, r, hit.hit_min, \
			hit.hit_side_cylinder);
	if (BONUS && cylinder.dir_base.base.material == MIRROR)
			color = get_color_mirror(norm_dir, r, hit.hit_min, scene);
	return (color);
}

t_vec3f	get_paraboloid_norm(t_hits hit, t_ray r, t_scene *scene)
{
	t_paraboloid	paraboloid;

	paraboloid = (((t_object *)(scene->objects.data))[hit.object_index]).paraboloid;
	return(paraboloid_normal(paraboloid, r, hit));
}

t_vec3f	get_paraboloid_color(t_hits hit, t_ray r, t_vec3f norm_dir, t_scene *scene)
{
	t_paraboloid	paraboloid;
	t_vec3f			color;

	paraboloid = (((t_object *)(scene->objects.data))[hit.object_index]).paraboloid;
	color = paraboloid.dir_base.base.color;
	if (BONUS && paraboloid.dir_base.base.material == CHECKER)
		color = get_color_checkerboard_paraboloid(paraboloid, r, \
			hit.hit_min);
	if (BONUS && paraboloid.dir_base.base.material == MIRROR)
			color = get_color_mirror(norm_dir, r, hit.hit_min, scene);
	return (color);
}
