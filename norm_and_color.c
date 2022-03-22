#include "miniRT.h"
#include <math.h>

t_vec3f	get_rotated_hit_point(t_plane plane, t_ray r, float hit_min)
{
	t_vec3f	hit_point;
	t_vec3f	norm_dir;
	t_angle	angle;

	norm_dir = plane_normal(plane.dir, r.dir);
	hit_point = at(r, hit_min);
	hit_point = vec3f_sub(hit_point, plane.pos);
	angle = get_angle(norm_dir);
	return (ft_rodrigues(hit_point, angle.k, angle.angle));
}

t_vec3f	mix_diffuse_and_smooth(t_hits hit, t_ray r,
		t_scene *scene, t_vec3f *norm_dir, t_vec3f color)
{
	t_vec3f	color1;
	t_vec3f	color2;
	float	ratio;
	t_plane	plane;

	plane = ((t_plane *)(scene->planes.data))[hit.object_index];
	color1 = get_color_mirror(*norm_dir, r, hit.hit_min, scene);
	color2 = plane.color;
	ratio = vec3f_len(color) / 3.;
	color = vec3f_mul(color1, ratio);
	color = vec3f_add(color, vec3f_mul(color2, 1 - ratio));
	return (color);
}

t_vec3f	get_sphere_norm_color(t_hits hit, t_ray r, \
	t_sphere *spheres, t_vec3f *norm_dir, t_scene *scene)
{
	t_sphere	sphere;
	t_vec3f		color;

	sphere = spheres[hit.object_index];
	color = sphere.color;
	*norm_dir = get_normal_bump_sphere(at(r, hit.hit_min), sphere.pos, sphere);
	if (sphere.texture.data)
		color = get_sphere_texture(sphere, r, hit);
	if (BONUS && sphere.material == CHECKER)
		color = get_color_checkerboard_sphere(*norm_dir, color);
	if (BONUS && sphere.material == MIRROR)
	{
		if (sphere.texture.data)
			color = mix_diffuse_and_smooth(hit, r, scene, norm_dir, color);
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

	plane = ((t_plane *)(scene->planes.data))[hit.object_index];
	color = plane.color;
	rotated_hit_point = get_rotated_hit_point(plane, r, hit.hit_min);
	plane_pos.x = fabsf(rotated_hit_point.x);
	plane_pos.y = fabsf(rotated_hit_point.z);
	*norm_dir = plane_normal_bump(plane_pos, plane, r.dir);
	if (plane.texture.data)
		color = get_plane_texture(plane, plane_pos);
	if (BONUS && plane.material == CHECKER)
		color = get_color_checkerboard_plane(plane, r, hit.hit_min, color);
	if (BONUS && plane.material == MIRROR)
	{
		if (plane.texture.data)
			color = mix_diffuse_and_smooth(hit, r, scene, norm_dir, color);
		else
			color = get_color_mirror(*norm_dir, r, hit.hit_min, scene);
	}
	return (color);
}

t_vec3f	get_cylinder_norm_color(t_hits hit, t_ray r, \
	t_cylinder *cylinders, t_vec3f *norm_dir)
{
	t_cylinder	cylinder;

	cylinder = cylinders[hit.object_index];
	if (hit.hit_side_cylinder)
		*norm_dir = cylinder_side_norm(at(r, hit.hit_min), cylinder);
	else
		*norm_dir = plane_normal(cylinder.dir, r.dir);
	if (BONUS && cylinder.material == CHECKER)
		return (get_color_checkerboard_cylinder(cylinder, r, hit.hit_min, \
			hit.hit_side_cylinder));
	return (cylinder.color);
}

t_vec3f	get_paraboloid_norm_color(t_hits hit, t_ray r, \
	t_paraboloid *paraboloids, t_vec3f *norm_dir)
{
	t_paraboloid	paraboloid;

	paraboloid = paraboloids[hit.object_index];
	*norm_dir = paraboloid_normal(paraboloid, r, hit);
	if (BONUS && paraboloid.material == CHECKER)
		return (get_color_checkerboard_paraboloid(paraboloid, r, \
			hit.hit_min));
	return (paraboloid.color);
}
