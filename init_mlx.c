#include "miniRT.h"
#include "mlx/mlx.h"
#include "vec/vec.h"
#include <math.h>

#define ASPECT_RATIO 1.7777777777
#define DESTROY_NOTIFY 17

void	get_lower_left_corner(t_info *info, t_scene *scene)
{
	t_vec3f		left_edge;
	t_vec3f		lower_left_corner1;
	t_vec3f		right;
	t_vec3f		up;

	up = vec3f_init(0, 1, 0);
	if (scene->camera->dir.x == 0 && scene->camera->dir.z == 0)
		up = vec3f_init(0, 0, 1);
	right = vec3f_cross(scene->camera->dir, up);
	right = vec3f_unit(right);
	up = vec3f_cross(right, scene->camera->dir);
	info->horizontal = vec3f_mul(right, info->viewport_width);
	info->vertical = vec3f_mul(up, info->viewport_height);
	left_edge = vec3f_sub(scene->camera->pos, vec3f_div(info->horizontal, 2));
	lower_left_corner1 = vec3f_sub(left_edge, vec3f_div(info->vertical, 2));
	info->lower_left_corner = vec3f_add(lower_left_corner1, \
		vec3f_mul(scene->camera->dir, info->focal_length));
}

void	init_mlx(t_scene *scene)
{
	t_info		info;

	info.mlx_ptr = mlx_init();
	info.win_height = (WIN_WIDTH / ASPECT_RATIO);
	info.win_ptr = mlx_new_window(info.mlx_ptr, WIN_WIDTH, info.win_height, \
		"miniRT");
	info.mlximg_ptr = mlx_new_image(info.mlx_ptr, WIN_WIDTH, info.win_height);
	init_image(&info);
	info.viewport_height = 2.0;
	info.viewport_width = ASPECT_RATIO * info.viewport_height;
	info.focal_length = (info.viewport_width / \
		tan(((scene->camera->fov / 180) * M_PI) / 2)) / 2;
	scene->camera->dir = vec3f_unit(scene->camera->dir);
	get_lower_left_corner(&info, scene);
	paint_img(&info, scene);
	mlx_hook(info.win_ptr, DESTROY_NOTIFY, 0, handle_destroy, NULL);
	mlx_expose_hook(info.win_ptr, draw_to_window, &info);
	mlx_key_hook(info.win_ptr, handle_key, &info);
	if (!PROFILE)
		mlx_loop(info.mlx_ptr);
}
