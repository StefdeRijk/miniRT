#include "miniRT.h"

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

/*
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
	r = rotate_ray(r, cylinder);
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
	r = rotate_ray(r, cylinder);
	printf("ray origin: ");
	vec3f_print(r.origin);
	printf("\nray dir: ");
	vec3f_print(r.dir);
	printf("\n");
}
*/

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
	printf("ray in right dir: %f\n", hit_infinite_cylinder(r, cylinder));
	r.dir = vec3f_init(0, -1, 0);
	printf("ray in right dir: %f\n", hit_infinite_cylinder(r, cylinder));
	r.dir = vec3f_init(1, 1, 1);
	printf("ray in right dir: %f\n", hit_infinite_cylinder(r, cylinder));
	r.dir = vec3f_init(0, -1.6, -1);
	printf("ray in right dir: %f\n", hit_infinite_cylinder(r, cylinder));
	r.dir = vec3f_init(0, -10.6, -1);
	printf("ray in right dir: %f\n", hit_infinite_cylinder(r, cylinder));
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
	r.origin = vec3f_init(0, 0.00001, 0);
	r.dir = vec3f_init(0, 0, -1);
	hit.hit_min = hit_paraboloid(paraboloid, r);
	printf("t: %f\n", hit.hit_min);
	normal = paraboloid_normal(paraboloid, r, hit); 
	vec3f_print(normal);
}
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

int main(void)
{
	/*
	test_reflection();
	test_normal();
	test_at();
	test_ray_color();
	test_ray_to_color();
	test_ray_bounce();
	*/
	//test_rotate_ray();
	//test_ray_in_right_dir();
	//test_hit_top_or_bottom();
	//test_hit_infinite_cylinder();
	//test_cylinder_shadow();
	test_hit_paraboloid();
}
