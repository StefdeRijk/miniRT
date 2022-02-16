#include "mlx/mlx.h"
#include "vec/vec.h"
#include <stdlib.h>
#include <math.h>
#include "miniRT.h"

#define WIN_WIDTH 2560
#define ASPECT_RATIO 1.7777777777
#define WIN_HEIGHT (WIN_WIDTH / ASPECT_RATIO)
#define DESTROY_NOTIFY 17

t_vec3f	get_ray_direction(t_info *info, int i, int j, t_vec3f camera)
{
	float	u;
	float	v;
	t_vec3f	hor_offset;
	t_vec3f	ver_offset;
	t_vec3f	direction;

	u = (float)i / (WIN_WIDTH - 1);
	v = (float)j / (WIN_HEIGHT - 1);
	hor_offset = vec3f_mul(info->horizontal, u);
	ver_offset = vec3f_mul(info->vertical, v);
	direction = vec3f_add(info->lower_left_corner, hor_offset);
	direction = vec3f_add(direction, ver_offset);
	direction = vec3f_sub(direction, camera);
	return (direction);
}

void	paint_img(t_info *info, t_vec3f camera, t_scene *scene)
{
	int		i;
	int		j;
	int		k;
	t_vec3f	direction;
	t_ray	r;
	t_vec3f	ray_colour = {0, 0, 0};
	int		color;
	t_vec3f	added_ray_color;

	j = WIN_HEIGHT - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < WIN_WIDTH)
		{
			k = 0;
			added_ray_color = vec3f_init(0, 0, 0);
			while (k < 5)
			{
				direction = get_ray_direction(info, i, j, camera);
				r.origin = camera;
				r.dir = direction;
				r.bounces = 0;
				ray_colour = ray_color(r, scene);
				added_ray_color = vec3f_add(added_ray_color, ray_colour);
				k++;
			}
			ray_colour = vec3f_div(added_ray_color, 5);
			color = ray_to_pixel_color(ray_colour);
			pixel_put_image(&info->img, i, WIN_HEIGHT - j - 1, color);
			i++;
		}
		j--;
	}
}

void init_mlx(t_scene *scene)
{
	t_info		info;
	t_vec3f		left_edge;
	t_vec3f		lower_left_corner1;
	t_vec3f		right;
	t_vec3f		up;

	info.mlx_ptr = mlx_init();
	info.win_ptr = mlx_new_window(info.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, \
	"miniRT");
	info.mlximg_ptr = mlx_new_image(info.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	init_image(&info);
	info.viewport_height = 2.0;
	info.viewport_width = ASPECT_RATIO * info.viewport_height;
	info.focal_length = (info.viewport_width / \
		tan(((scene->camera->fov / 180) * M_PI) / 2)) / 2;
	scene->camera->dir = vec3f_unit(scene->camera->dir);
	up = vec3f_init(0, 1, 0);
	if (scene->camera->dir.x == 0 && scene->camera->dir.z == 0)
		up = vec3f_init(0, 0, 1);
	right = vec3f_cross(scene->camera->dir, up);
	right = vec3f_unit(right);
	up = vec3f_cross(right, scene->camera->dir);
	info.horizontal = vec3f_mul(right, info.viewport_width);
	info.vertical = vec3f_mul(up, info.viewport_height);
	left_edge = vec3f_sub(scene->camera->pos, vec3f_div(info.horizontal, 2));
	lower_left_corner1 = vec3f_sub(left_edge, vec3f_div(info.vertical, 2));
	info.lower_left_corner = vec3f_add(lower_left_corner1, \
		vec3f_mul(scene->camera->dir, info.focal_length));
	paint_img(&info, scene->camera->pos, scene);
	mlx_hook(info.win_ptr, DESTROY_NOTIFY, 0, handle_destroy, NULL);
	mlx_expose_hook(info.win_ptr, draw_to_window, &info);
	mlx_key_hook(info.win_ptr, handle_key, &info);
	mlx_loop(info.mlx_ptr);
}
