#include "miniRT.h"
#include <assert.h>
#include <math.h>

/*
void	test_reflection(void)
{
	static t_vec3f	incoming = {1, -1, 1};
	static t_vec3f	normal = {0, 1, 0};
	t_vec3f			result;

	result = f_reflection(incoming, normal);
	printf("------ Reflection -----\n");
	vec3f_print(result);
	printf("\n");
}

void	test_normal(void)
{
	static t_vec3f	hit_point = {0, 0, 1};
	static t_vec3f	sphere_center = {0, -1, 1};
	t_vec3f			normal;

	normal = get_normal_sphere(hit_point, sphere_center);
	printf("------ Normal -----\n");
	vec3f_print(normal);
	printf("\n");
}

void	test_at(void)
{
	t_ray	r;
	float	distance;
	t_vec3f	new_at;

	r.origin = vec3f_init(0, 0, 1);
	r.dir = vec3f_init(1, 1, 0);
	distance = 5;
	new_at = at(r, distance);
	printf("------ AT -----\n");
	vec3f_print(new_at);
	printf("\n");
}

void	test_ray_color(void)
{
	t_ray			r;
	static t_scene	scene = {};
	t_vec3f			color;

	get_scene("test_light.rt", &scene);
	r.origin = vec3f_init(0, 0, 0);
	r.dir = vec3f_init(0, 0, -1);
	color = ray_color(r, &scene);
	printf("------ Ray Color -----\n");
	vec3f_print(color);
	printf("\n");
}
*/

/*
void	test_ray_to_color(void)
{
	static t_vec3f	ray_color = {0, 0, 0};
	int				color;

	color = sphere_to_pixel_color(ray_color);
	printf("------ Ray color to color int -----\n");
	printf("color = %i\n", color);
	printf("\n");
}
*/

/*
void	test_ray_bounce(void)
{
	t_ray			r;
	static t_scene	scene = {0};

	get_scene("test_light.rt", &scene);
	r.origin = vec3f_init(0, 0, 0);
	r.dir = vec3f_init(0, 0, -1);
	printf("------ Ray Bounce -----\n");
	ray_color(r, &scene);
	printf("\n");
}

void	test_rotate_ray(void)
{
	t_ray				r;
	t_cylinder			*c;
	t_cylinder			cylinder;
	static t_scene		scene = {0};

	printf("------ Rotate ray-----\n");
	get_scene("test_cylinder.rt", &scene);
	c = scene.cylinders.data;
	cylinder = *c;
	r.origin = vec3f_init(0, 0, 1);
	r.dir = vec3f_init(0, 0, -1);
	r = rotate_ray(r, cylinder.pos, cylinder.dir);
	printf("ray origin: ");
	vec3f_print(r.origin);
	printf("\nray dir: ");
	vec3f_print(r.dir);
	printf("\n");
	cylinder.dir.x = 0;
	cylinder.dir.y = 1;
	cylinder.dir.z = 0;
	r.origin = vec3f_init(0, 0, 0);
	r.dir = vec3f_init(0, 0, -1);
	r = rotate_ray(r, cylinder.pos, cylinder.dir);
	printf("ray origin: ");
	vec3f_print(r.origin);
	printf("\nray dir: ");
	vec3f_print(r.dir);
	printf("\n");
}

void	test_ray_in_right_dir(void)
{
	t_ray			r;
	t_cylinder		*c;
	t_cylinder		cylinder;
	static t_scene	scene = {0};

	printf("------ Ray in right dir-----\n");
	get_scene("test_cylinder2.rt", &scene);
	c = scene.cylinders.data;
	cylinder = *c;
	r.origin = vec3f_init(0, -4, 0);
	r.dir = vec3f_init(0, 1, 0);
	printf("ray in right dir: %d\n", ray_in_right_dir(r, cylinder));
	r.dir = vec3f_init(0, -1, 0);
	printf("ray in right dir: %d\n", ray_in_right_dir(r, cylinder));
	r.dir = vec3f_init(1, 0.1, 1);
	printf("ray in right dir: %d\n", ray_in_right_dir(r, cylinder));
}

void	test_hit_top_or_bottom(void)
{
	t_ray			r;
	t_cylinder		*c;
	t_cylinder		cylinder;
	static t_scene	scene = {0};

	printf("------ Hit top or bottom ----\n");
	get_scene("test_cylinder2.rt", &scene);
	c = scene.cylinders.data;
	cylinder = *c;
	r.origin = vec3f_init(0, -4, 0);
	r.dir = vec3f_init(0, 1, 0);
	printf("ray in right dir: %f\n", hit_top_or_bottom(r, cylinder));
	r.dir = vec3f_init(0, -1, 0);
	printf("ray in right dir: %f\n", hit_top_or_bottom(r, cylinder));
	r.dir = vec3f_init(1, 1, 1);
	printf("ray in right dir: %f\n", hit_top_or_bottom(r, cylinder));
	r.origin = vec3f_init(0, -0.6, 0);
	printf("ray in right dir: %f\n", hit_top_or_bottom(r, cylinder));
}

void	test_hit_infinite_cylinder(void)
{
	t_ray			r;
	t_cylinder		*c;
	t_cylinder		cylinder;
	static t_scene	scene = {0};

	printf("------ Hit infinite cylinder ----\n");
	get_scene("test_cylinder3.rt", &scene);
	c = scene.cylinders.data;
	cylinder = *c;
	r.origin = vec3f_init(0, 0, 4);
	r.dir = vec3f_init(0, 0, -1);
	printf("hit: %f\n", hit_infinite_cylinder(r, cylinder));
	r.dir = vec3f_init(0, -1, 0);
	printf("hit: %f\n", hit_infinite_cylinder(r, cylinder));
	r.dir = vec3f_init(1, 1, 1);
	printf("hit: %f\n", hit_infinite_cylinder(r, cylinder));
	r.dir = vec3f_init(0, -1.6, -1);
	printf("hit: %f\n", hit_infinite_cylinder(r, cylinder));
	r.dir = vec3f_init(0, -10.6, -1);
	printf("hit: %f\n", hit_infinite_cylinder(r, cylinder));
}

void	test_hit_cylinder(void)
{
	t_ray			r;
	t_cylinder		*c;
	t_cylinder		cylinder;
	static t_scene	scene = {0};
	int 			hit_side;

	printf("------ Hit cylinder ----\n");
	get_scene("cylinder_problem2.rt", &scene);
	c = scene.cylinders.data;
	cylinder = *c;
	r.origin = vec3f_init(1, 1, 4);
	r.dir = vec3f_init(0, 0, -1);
	printf("%f\n", hit_cylinder(cylinder, r, &hit_side));
	r.dir = vec3f_init(1, -1, -1);
	printf("%f\n", hit_cylinder(cylinder, r, &hit_side));
}

void	test_hit_paraboloid(void)
{
	t_ray			r;
	t_paraboloid	*p;
	t_paraboloid	paraboloid;
	static t_scene	scene = {0};
	t_vec3f 		normal;
	t_hits			hit;

	printf("------ Hit paraboloid ----\n");
	get_scene("test_paraboloid.rt", &scene);
	p = scene.paraboloids.data;
	paraboloid = *p;
	r.origin = vec3f_init(0.0001, 0, 0);
	r.dir = vec3f_init(0, 1, 0);
	hit.hit_min = hit_paraboloid(paraboloid, r);
	printf("t: %f\n", hit.hit_min);
	normal = paraboloid_normal(paraboloid, r, hit); 
	vec3f_print(normal);
}
*/

/*
void	test_cylinder_shadow(void)
{
	t_ray			r;
	static t_scene	scene = {0};
	t_hits			hit;
	t_hits			shadow_hit;
	t_vec3f			hit_pos;
	t_ray			to_spot;
	t_vec3f			reverse_r_dir;
	t_vec3f			offset;
	t_ray			rot_ray;
	t_cylinder		*c;

	printf("------ Check cylinder shadow----\n");
	get_scene("test_cylinder_shadow.rt", &scene);
	c = scene.cylinders.data;
	r.origin = vec3f_init(0, 0, 0);
	r.dir = vec3f_init(0, 0, -1);
	//vec3f_print(ray_color(r, &scene));
	printf("calling get hit\n");
	get_hit(&hit, &scene, r);
	hit_pos = at(r, hit.hit_min);
	//vec3f_print(hit_pos);
	to_spot.dir = vec3f_unit(vec3f_sub(scene.light->pos, hit_pos));
	//printf("to_spot dir: ");
	//vec3f_print(to_spot.dir);
	reverse_r_dir = vec3f_sub(vec3f_init(0, 0, 0), r.dir);
	offset = vec3f_mul(reverse_r_dir, 0.1);
	to_spot.origin = vec3f_add(hit_pos, offset);
	rot_ray = rotate_ray(to_spot, *c);
	//printf("rot ray y: %f\n", rot_ray.dir.y);
	//printf("in shadow: %d\n", in_shadow(to_spot.dir, hit_pos, &scene, r));
	scene.distance_to_spot = vec3f_len(vec3f_sub(scene.light->pos, hit_pos));
	printf("distance to spot: %f\n", scene.distance_to_spot);
	cylinder_loop_shadow(to_spot, &scene, &shadow_hit);
	printf("shadow hit_min: %f\n", shadow_hit.hit_min);
	printf("in shadow: %d\n", get_hit_shadow(&scene, to_spot, hit_pos));
}
*/

void test_get_angle_to() {
	t_angle result;

	printf("------ Get_angle_to ----\n");
	result = get_angle_to(vec3f_init(1,0,0), vec3f_init(-1,0,0));
	printf("from x to -x, angle: %f, k", result.angle);
	vec3f_print(result.k);

	result = get_angle_to(vec3f_init(1,0,0), vec3f_init(0,0,-1));
	printf("from x to -z, angle: %f, k", result.angle);
	vec3f_print(result.k);
}

void test_rodrigues() {
	t_angle angle;

	printf("------ Rodrigues ----\n");
	angle.angle = M_PI;
	angle.k = vec3f_init(0, 0, 1);
	t_vec3f result = ft_rodrigues(vec3f_init(1, 0, 0), angle.k, angle.angle);
	printf("turning (1, 0, 0) to (-1, 0, 0):\n");
	vec3f_print(result);
}

void print_bump_test(t_vec3f bump, t_vec3f normal) {
	t_vec3f result;

	printf("\nnormal: ");
	vec3f_print(normal);
	printf("bump: ");
	vec3f_print(bump);
	printf("result: ");
	result = rotate_bump_to_sphere_normal(bump, normal);
	vec3f_print(result);
}

void test_add_bump_to_normal() {
	printf("------ Add bump to normal ----\n");
	t_vec3f normal = vec3f_init(0, 0, -1);
	t_vec3f bump_normal = vec3f_init(0, 0, -1);
	print_bump_test(bump_normal, normal);

	normal = vec3f_init(0, 0, 1);
	bump_normal = vec3f_init(0, 0, -1);
	print_bump_test(bump_normal, normal);

	normal = vec3f_unit(vec3f_init(1, 0, 0));
	bump_normal = vec3f_init(0, 0, -1);
	print_bump_test(bump_normal, normal);

	normal = vec3f_unit(vec3f_init(1, 0, 1));
	bump_normal = vec3f_init(0, 0, -1);
	print_bump_test(bump_normal, normal);

	normal = vec3f_unit(vec3f_init(1, 0, -1));
	bump_normal = vec3f_init(0, 0, -1);
	print_bump_test(bump_normal, normal);

	normal = vec3f_unit(vec3f_init(1, 0, 0));
	bump_normal = vec3f_init(1, 0, -1);
	print_bump_test(bump_normal, normal);

	normal = vec3f_unit(vec3f_init(0.001, 0, 1));
	bump_normal = vec3f_init(1, 0, -1);
	print_bump_test(bump_normal, normal);

	normal = vec3f_unit(vec3f_init(-0.001, 0, 1));
	bump_normal = vec3f_init(1, 0, -1);
	print_bump_test(bump_normal, normal);

	normal = vec3f_unit(vec3f_init(0, 0.001, 1));
	bump_normal = vec3f_init(1, 0, -1);
	print_bump_test(bump_normal, normal);

	normal = vec3f_unit(vec3f_init(0, -0.001, 1));
	bump_normal = vec3f_init(1, 0, -1);
	print_bump_test(bump_normal, normal);

	/*
	normal = vec3f_unit(vec3f_init(0, 0, -1));
	bump_normal = vec3f_init(1, 0, 0);
	print_bump_test(bump_normal, normal);

	normal = vec3f_unit(vec3f_init(0, 0, -1));
	bump_normal = vec3f_init(0, 1, 0);
	print_bump_test(bump_normal, normal);

	normal = vec3f_unit(vec3f_init(0, 0, 1));
	bump_normal = vec3f_init(0, 1, 0);
	print_bump_test(bump_normal, normal);

	normal = vec3f_unit(vec3f_init(0, 0, -1));
	bump_normal = vec3f_init(1, 0, 0);
	print_bump_test(bump_normal, normal);

	normal = vec3f_unit(vec3f_init(0, 0, 1));
	bump_normal = vec3f_init(1, 0, 0);
	print_bump_test(bump_normal, normal);
	*/
}

void test_rodrigues_consitency() {
	t_vec3f result;
	t_angle angle;

	printf("------ Rodrigues consitency ----\n");
	printf("turning (1, 0, 0) to itself\n");
	t_vec3f dir = vec3f_init(1, 0, 0);
	t_vec3f to = vec3f_init(1, 0, 0);
	angle = get_angle_to(dir, to);
	result = ft_rodrigues(dir, angle.k, angle.angle);
	assert(vec3f_equal(result, to));

	printf("turning (1, 0, 0) to (-1, 0, 0)\n");
	dir = vec3f_init(1, 0, 0);
	to = vec3f_init(-1, 0, 0);
	angle = get_angle_to(dir, to);
	result = ft_rodrigues(dir, angle.k, angle.angle);
	assert(vec3f_almost_equal(result, to));
}

void	test_plane_reflection()
{
	t_plane	plane;
	t_ray	r;
	t_vec3f	reflection;
	
	printf("------ Plane reflection ----\n");
	printf("reflecting (0, -0.5, -1) on (0, 1, 0)\n");

	plane.dir_base.dir = vec3f_init(0.00, -1, 0.00);
	plane.dir_base.base.pos = vec3f_init(0, 0, 0);
	r.origin = vec3f_init(0, 1, 0);
	r.dir = vec3f_init(2, 1.5, -1);

	reflection = f_reflection(r.dir, plane.dir_base.dir);
	vec3f_print(reflection);
}
/*
int main(void)
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
	//test_reflection();
	//test_normal();
	//test_at();
	//test_ray_color();
	//test_ray_to_color();
	//test_ray_bounce();
	//test_rotate_ray();
	//test_ray_in_right_dir();
	//test_hit_top_or_bottom();
	//test_hit_infinite_cylinder();
	//test_hit_cylinder();
	//test_cylinder_shadow();
	//test_hit_paraboloid();
	// test_get_angle_to();
	// test_rodrigues();
	// test_rodrigues_consitency();
	// test_add_bump_to_normal();
	test_plane_reflection();
}

*/
int main() {
}
