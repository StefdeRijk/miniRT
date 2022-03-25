#include "miniRT.h"

void	init_image(t_info *info)
{
	int	bits_per_pixel;
	int	line_length;
	int	endian;

	info->img.data = (int *)mlx_get_data_addr(info->mlximg_ptr, \
		&bits_per_pixel, &line_length, &endian);
	info->img.size_x = line_length / sizeof(int);
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
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->mlximg_ptr, \
		0, 0);
	return (0);
}

void	pixel_put_image(t_arr2di *image, int x, int y, int color)
{
	*(unsigned int *)(image->data + x + y * image->size_x) \
		= color;
}
