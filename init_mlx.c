#include "mlx/mlx.h"
# include "vec/vec.h"
# include <stdlib.h>
# include <math.h>
# include "miniRT.h"

# define WIN_WIDTH 300
# define ASPECT_RATIO (16./9.)
# define WIN_HEIGHT (WIN_WIDTH / ASPECT_RATIO)
# define DESTROY_NOTIFY 17
typedef struct s_arr2di {
	int	*data;
	int	size_x;
	int	size_y;
}	t_arr2di;

typedef struct s_info {
	void			*mlx_ptr;
	void			*win_ptr;
	void			*mlximg_ptr;
	t_arr2di		img;
}	t_info;

typedef struct s_ray {
	t_vec3f origin;
	t_vec3f dir;
} t_ray;

void	init_image(t_info *info)
{
	int	bits_per_pixel;
	int	line_length;
	int	endian;

	info->img.data = (int *)mlx_get_data_addr(info->mlximg_ptr, &bits_per_pixel,
			&line_length, &endian);
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
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->mlximg_ptr,
		0, 0);
	return (0);
}

void	pixel_put_image(t_arr2di *image, int x, int y, int color)
{
	*(unsigned int *)(image->data + x + y * image->size_x)
		= color;
}

int	trgb_to_int(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	rgb_to_color(t_vec3i color)
{
	return (trgb_to_int(0, color.r, color.g, color.b));
}

t_vec3i	color_to_rgb(int color)
{
	t_vec3i	rgb;

	rgb.r = (color & (0xFF << 16)) >> 16;
	rgb.g = (color & (0xFF << 8)) >> 8;
	rgb.b = color & 0xFF;
	return (rgb);
}


int	hit_sphere(t_sphere sphere, t_ray r)
{
	t_vec3f oc = vec3f_sub(r.origin, sphere.pos);
	float a = vec3f_len_sq(r.dir);
	float b = 2.0 * vec3f_dot(oc, r.dir);
	float c = vec3f_len_sq(oc) - (sphere.radius * sphere.radius);
	float d = b*b - 4*a*c;

	return (d > 0);
}

int ray_color(t_ray r, t_sphere sphere)
{
	if (hit_sphere(sphere, r))
	{
		return(rgb_to_color(sphere.color));
	}
	t_vec3f unit_dir = vec3f_unit(r.dir);
	printf("%f ", unit_dir.x);
	return (trgb_to_int(0, fabs(unit_dir.x) * 255, fabs(unit_dir.y) * 255, fabs(unit_dir.z) * 255));
}

void init_mlx() {
	t_sphere sphere;
	   
	sphere.pos = vec3f_init(0, 0, -10);
	sphere.radius = 1.;
	sphere.color = vec3i_init(200, 100, 200);

	t_info	info;

	info.mlx_ptr = mlx_init();
	info.win_ptr = mlx_new_window(info.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"miniRT");
	info.mlximg_ptr = mlx_new_image(info.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	init_image(&info);

	pixel_put_image(&info.img, 50, 50, 65535);

	float viewport_height = 2.0;
	float viewport_width = ASPECT_RATIO * viewport_height;
	
	float focal_length = 10;

	t_vec3f camera = {0,0,0};

	t_vec3f horizontal = {viewport_width, 0, 0};
	t_vec3f vertical = {0, viewport_height, 0};

	t_vec3f left_edge = vec3f_sub(camera, vec3f_div(horizontal, 2));
	t_vec3f lower_left_corner1 = vec3f_sub(left_edge, vec3f_div(vertical, 2));
	t_vec3f lower_left_corner = vec3f_sub(lower_left_corner1, vec3f_init(0, 0, focal_length));

	int j = WIN_HEIGHT-1;
	while (j >= 0)
	{
		int i = 0;
		while (i < WIN_WIDTH)
		{
			float u = (float)i / (WIN_WIDTH - 1);
			float v = (float)j / (WIN_HEIGHT- 1);
			t_vec3f hor_offset = vec3f_mul(horizontal, u);
			t_vec3f ver_offset = vec3f_mul(vertical, v);
			t_vec3f win_pos = vec3f_add(lower_left_corner, hor_offset);
			win_pos = vec3f_add(win_pos, ver_offset);
			t_vec3f direction = vec3f_sub(win_pos, camera);
			t_ray r = {camera, direction};
			int color = ray_color(r, sphere);
			pixel_put_image(&info.img, i, j, color);
			i++;
		}
		j--;
	}

	mlx_hook(info.win_ptr, DESTROY_NOTIFY, 0, handle_destroy, NULL);
	mlx_expose_hook(info.win_ptr, draw_to_window, &info);
	mlx_key_hook(info.win_ptr, handle_key, &info);
	mlx_loop(info.mlx_ptr);
}


