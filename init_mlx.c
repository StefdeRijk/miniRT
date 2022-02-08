#include "mlx/mlx.h"
# include "vec/vec.h"
# include <stdlib.h>

# define SCREEN_WIDTH 100
# define SCREEN_HEIGHT 100
# define DESTROY_NOTIFY 17
typedef struct s_arr2di {
	int	*data;
	int	stride_y;
	int	size_y;
}	t_arr2di;

typedef struct s_arr2dc {
	char	*data;
	int		stride_x;
	int		stride_y;
	int		size_y;
}	t_arr2dc;

typedef struct s_pixel_trans {
	t_vec2f	offset;
	float	xy_scale;
	float	z_scale;
}	t_pixel_trans;


typedef struct s_info {
	void			*mlx_ptr;
	void			*win_ptr;
	void			*mlximg_ptr;
	t_arr2dc		img;
	t_arr2di		grid;
	t_pixel_trans	pxt;
	int				min_z;
	int				max_z;
	t_arr2di		colors;
	int				max_step_size;
}	t_info;

void	init_image(t_info *info)
{
	int	bits_per_pixel;
	int	line_length;
	int	endian;

	info->img.data = mlx_get_data_addr(info->mlximg_ptr, &bits_per_pixel,
			&line_length, &endian);
	info->img.stride_x = bits_per_pixel / 8;
	info->img.stride_y = line_length;
}

int	handle_key(int keycode, void *param)
{
	(void)param;
	if (keycode == 53)
		exit(0);
	return (0);
}

int	handle_destroy(void *param)
{
	(void)param;
	exit(0);
}
int	draw_to_window(t_info *info)
{
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->mlximg_ptr,
		0, 0);
	return (0);
}

void	pixel_put_image(t_arr2dc *image, int x, int y, int color)
{
	*(unsigned int *)(image->data + x * image->stride_x + y * image->stride_y)
		= color;
}

void init_mlx() {
	t_info	info;

	info.mlx_ptr = mlx_init();
	info.win_ptr = mlx_new_window(info.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
			"fdf");
	info.mlximg_ptr = mlx_new_image(info.mlx_ptr, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	init_image(&info);

	pixel_put_image(&info.img, 50, 50, 65535);

	mlx_hook(info.win_ptr, DESTROY_NOTIFY, 0, handle_destroy, NULL);
	mlx_expose_hook(info.win_ptr, draw_to_window, &info);
	mlx_key_hook(info.win_ptr, handle_key, &info);
	mlx_loop(info.mlx_ptr);
}


