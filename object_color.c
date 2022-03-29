#include "miniRT.h"
#include <math.h>

t_vec3f	mix_diffuse_and_smooth(t_colors colors)
{
	float	ratio;
	t_vec3f	color;

	ratio = vec3f_len_sq(colors.ratio_color) / 3.;
	color = vec3f_mul(colors.color_1, ratio);
	color = vec3f_add(color, vec3f_mul(colors.color_2, 1 - ratio));
	return (color);
}

t_vec3f	get_sphere_color(t_hits hit, t_ray r, t_vec3f norm_dir, t_scene *scene)
{
	t_sphere		sphere;
	t_vec3f			final_color;
	t_old_new_ray	rays;
	t_colors		colors;

	sphere = (((t_object *)(scene->objects.data))[hit.object_index]).sphere;
	final_color = sphere.base.color;
	if (BONUS && sphere.base.texture.data)
		final_color = get_sphere_texture(sphere, r, hit);
	if (BONUS && sphere.base.material == CHECKER)
		final_color = get_color_checkerboard_sphere(get_normal_sphere(\
			at(r, hit.hit_min), sphere.base.pos), final_color);
	if (BONUS && sphere.base.material == MIRROR)
	{
		rays.n = new_ray(r, norm_dir, hit.hit_min);
		rays.o = r;
		colors.ratio_color = final_color;
		colors.color_2 = spot_and_ambient(rays, sphere.base.color, \
			scene, norm_dir);
		final_color = get_color_mirror(norm_dir, r, hit.hit_min, scene);
		colors.color_1 = final_color;
		if (sphere.base.texture.data)
			final_color = mix_diffuse_and_smooth(colors);
	}
	return (final_color);
}

t_vec3f	get_plane_color(t_hits hit, t_ray r, \
		t_vec3f norm_dir, t_scene *scene)
{
	t_plane			plane;
	t_vec3f			final_color;
	t_old_new_ray	rays;
	t_colors		colors;

	plane = (((t_object *)(scene->objects.data))[hit.object_index]).plane;
	final_color = plane.dir_base.base.color;
	if (BONUS && plane.dir_base.base.texture.data)
		final_color = get_plane_texture(plane, get_plane_pos(hit, r, plane));
	if (BONUS && plane.dir_base.base.material == CHECKER)
		final_color = get_color_checkerboard_plane(plane, r, \
			hit.hit_min, final_color);
	if (BONUS && plane.dir_base.base.material == MIRROR)
	{
		rays.n = new_ray(r, norm_dir, hit.hit_min);
		rays.o = r;
		colors.ratio_color = final_color;
		colors.color_2 = spot_and_ambient(rays, plane.dir_base.base.color, \
			scene, norm_dir);
		final_color = get_color_mirror(norm_dir, r, hit.hit_min, scene);
		colors.color_1 = final_color;
		if (plane.dir_base.base.texture.data)
			final_color = mix_diffuse_and_smooth(colors);
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
