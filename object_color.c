#include "miniRT.h"
#include <math.h>

t_vec3f	mix_diffuse_and_smooth(t_hits hit, t_scene *scene, \
	t_vec3f color1, t_vec3f base_color)
{
	float	ratio;
	t_vec3f	color;
	t_vec3f	color2;

	color2 = (((t_object *)(scene->objects.data))[hit.object_index]).base.color;
	ratio = vec3f_len_sq(base_color) / 3.;
	color = vec3f_mul(color1, ratio);
	color = vec3f_add(color, vec3f_mul(color2, 1 - ratio));
	return (color);
}

t_vec3f	get_sphere_color(t_hits hit, t_ray r, t_vec3f norm_dir, t_scene *scene)
{
	t_sphere	sphere;
	t_vec3f		final_color;
	t_vec3f		base_color;
	t_vec3f		sphere_norm;

	sphere = (((t_object *)(scene->objects.data))[hit.object_index]).sphere;
	final_color = sphere.base.color;
	sphere_norm = get_normal_sphere(at(r, hit.hit_min), sphere.base.pos);
	if (BONUS && sphere.base.texture.data)
		final_color = get_sphere_texture(sphere, r, hit);
	if (BONUS && sphere.base.material == CHECKER)
		final_color = get_color_checkerboard_sphere(sphere_norm, final_color);
	if (BONUS && sphere.base.material == MIRROR)
	{
		base_color = final_color;
		final_color = get_color_mirror(norm_dir, r, hit.hit_min, scene);
		if (sphere.base.texture.data)
			final_color = mix_diffuse_and_smooth(hit, scene, \
				final_color, base_color);
	}
	return (final_color);
}

t_vec3f	get_plane_color(t_hits hit, t_ray r, \
		t_vec3f norm_dir, t_scene *scene)
{
	t_plane	plane;
	t_vec3f	plane_pos;
	t_vec3f	base_color;
	t_vec3f	final_color;

	plane = (((t_object *)(scene->objects.data))[hit.object_index]).plane;
	plane_pos = get_plane_pos(hit, r, plane);
	final_color = plane.dir_base.base.color;
	if (BONUS && plane.dir_base.base.texture.data)
		final_color = get_plane_texture(plane, plane_pos);
	if (BONUS && plane.dir_base.base.material == CHECKER)
		final_color = get_color_checkerboard_plane(plane, r, \
			hit.hit_min, final_color);
	if (BONUS && plane.dir_base.base.material == MIRROR)
	{
		base_color = final_color;
		final_color = get_color_mirror(norm_dir, r, hit.hit_min, scene);
		if (plane.dir_base.base.texture.data)
			final_color = mix_diffuse_and_smooth(hit, scene, \
				final_color, base_color);
	}
	return (final_color);
}

t_vec3f	get_cylinder_color(t_hits hit, t_ray r, t_vec3f norm_dir, \
	t_scene *scene)
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

t_vec3f	get_paraboloid_color(t_hits hit, t_ray r, t_vec3f norm_dir, \
	t_scene *scene)
{
	t_paraboloid	paraboloid;
	t_vec3f			color;

	paraboloid = (((t_object *)(scene->objects.data)) \
		[hit.object_index]).paraboloid;
	color = paraboloid.dir_base.base.color;
	if (BONUS && paraboloid.dir_base.base.material == CHECKER)
		color = get_color_checkerboard_paraboloid(paraboloid, r, \
			hit.hit_min);
	if (BONUS && paraboloid.dir_base.base.material == MIRROR)
			color = get_color_mirror(norm_dir, r, hit.hit_min, scene);
	return (color);
}
