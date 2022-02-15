#include "miniRT.h"

void    test_reflection(void)
{
    t_vec3f incoming = {1, -1, 1};
    t_vec3f normal = {0, 1, 0};
    t_vec3f result;

    result = f_reflection(incoming, normal);
    printf("------ Reflection -----\n");
    vec3f_print(result);
    printf("\n");
}

void    test_normal(void)
{
    t_vec3f hit_point = {0, 0, 1};
    t_vec3f sphere_center = {0, -1, 1};
    t_vec3f normal;

    normal = get_normal_sphere(hit_point, sphere_center);
    printf("------ Normal -----\n");
    vec3f_print(normal);
    printf("\n");
}

void    test_at(void)
{
    t_ray   r;
    float   distance;
    t_vec3f new_at;

    r.origin = vec3f_init(0, 0, 1);
    r.dir = vec3f_init(1, 1, 0);
    distance = 5;
    new_at = at(r, distance);
    printf("------ AT -----\n");
    vec3f_print(new_at);
    printf("\n");
}

void    test_ray_color(void)
{
    t_ray   r;
    t_scene scene = {};
    t_vec3f color;

    get_scene("test_light.rt", &scene);
    r.origin = vec3f_init(0, 0, 0);
    r.dir = vec3f_init(0, 0, -1);
    color = ray_color(r, &scene);
    printf("------ Ray Color -----\n");
    vec3f_print(color);
    printf("\n");
}

void    test_ray_to_color(void)
{
    t_vec3f ray_color = {0, 0, 0};
    int     color;

    color = sphere_to_pixel_color(ray_color);
    printf("------ Ray color to color int -----\n");
    printf("color = %i\n", color);
    printf("\n");
}

void    test_ray_bounce(void)
{
    t_ray   r;
    t_scene scene = {};

    get_scene("test_light.rt", &scene);
    r.origin = vec3f_init(0, 0, 0);
    r.dir = vec3f_init(0, 0, -1);
    printf("------ Ray Bounce -----\n");
    ray_color(r, &scene);
    printf("\n");
}

void	test_rotate_ray(void)
{
	t_ray r;
	t_cylinder *c;
	t_cylinder cylinder;
	t_scene scene = {};

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

void	test_ray_in_right_dir(void)
{
	t_ray r;
	t_cylinder *c;
	t_cylinder cylinder;
	t_scene scene = {};

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
	t_ray r;
	t_cylinder *c;
	t_cylinder cylinder;
	t_scene scene = {};

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
	t_ray r;
	t_cylinder *c;
	t_cylinder cylinder;
	t_scene scene = {};

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
	test_rotate_ray();
	//test_ray_in_right_dir();
	//test_hit_top_or_bottom();
	//test_hit_infinite_cylinder();
}
