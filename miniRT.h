#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "stdlib.h"
# include "vec/vec.h"
# include "fcntl.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include "mlx/mlx.h"

typedef struct s_ambient {
	float	brightness;
	t_vec3f	color;
}	t_ambient;

typedef struct s_camera {
	t_vec3f	pos;
	t_vec3f	dir;
	float	fov;
}	t_camera;

typedef struct s_light {
	t_vec3f	pos;
	float	brightness;
	t_vec3f	color;
}	t_light;

typedef struct s_sphere {
	t_vec3f	pos;
	float	radius;
	t_vec3f	color;
	char	material;
}	t_sphere;

typedef struct s_plane {
	t_vec3f	pos;
	t_vec3f	dir;
	t_vec3f	color;
	char	material;
}	t_plane;

typedef struct s_cylinder {
	t_vec3f	pos;
	t_vec3f	dir;
	float	radius;
	float	height;
	t_vec3f	color;
	char	material;
}	t_cylinder;

typedef enum e_scene_elem_type {
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	NR_ELEM_TYPES
}	t_scene_elem_type;

typedef struct s_scene {
	t_ambient			*ambient;
	t_camera			*camera;
	t_light				*light;
	t_vec				spheres;
	t_vec				planes;
	t_vec				cylinders;

	t_scene_elem_type	prev_hit;
}	t_scene;

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
	t_vec3f			horizontal;
	t_vec3f			vertical;
	t_vec3f			lower_left_corner;
	float			viewport_height;
	float			viewport_width;
	float			focal_length;
	float			win_height;
}	t_info;

typedef struct s_ray {
	t_vec3f	origin;
	t_vec3f	dir;
	int		bounces;
}	t_ray;

typedef enum e_error {
	MRT_SUCCESS,
	MRT_ERROR
}	t_error;

typedef struct s_parse_line {
	char	*line;
	int		i;
	int		line_nr;
}	t_parse_line;

typedef struct s_angle {
	t_vec3f	k;
	float	angle;
}	t_angle;

typedef struct s_hits {
	float				hit_min;
	int					object_index;
	t_scene_elem_type	hit_type;
	int					hit_side_cylinder;
}	t_hits;

typedef void	(*t_elem_parser)(t_parse_line *line, t_scene *scene);

void	skip_one_char(t_parse_line *line, char c);
void	skip_zero_or_more_char(t_parse_line *line, char c);
void	skip_one_or_more_char(t_parse_line *line, char c);
char	line_next(t_parse_line *line);

void	parse_elem_type(t_parse_line *line, t_scene_elem_type *t);
void	parse_ambient(t_parse_line *line, t_scene *scene);
void	parse_camera(t_parse_line *line, t_scene *scene);
void	parse_light(t_parse_line *line, t_scene *scene);
void	parse_sphere(t_parse_line *line, t_scene *scene);
void	parse_plane(t_parse_line *line, t_scene *scene);
void	parse_cylinder(t_parse_line *line, t_scene *scene);
void	parse_line(t_parse_line line, t_scene *scene);
void	parse_int(t_parse_line *line, int *i);
void	parse_float(t_parse_line *line, float *f);
void	parse_vec3i(t_parse_line *line, t_vec3i *v);
void	parse_vec3f(t_parse_line *line, t_vec3f *v);
void	parse_char(t_parse_line *line, char *c);
void	parse_line(t_parse_line line, t_scene *scene);

void	check_in_set(t_parse_line *line, char *c, char *set);
void	check_range_f(t_parse_line *line, float f, float min, float max);
void	check_range_vec3f(t_parse_line *line, t_vec3f v, float min, float max);
void	check_range_i(t_parse_line *line, int i, int min, int max);
void	check_range_vec3i(t_parse_line *line, t_vec3i v, int min, int max);
void	check_range_f_exc(t_parse_line *line, float f, float min, float max);
void	parse_check_float(t_parse_line *line, float *f, float min, float max);
void	parse_check_float_exc(t_parse_line *line, float *f, \
		float min, float max);
void	parse_check_int(t_parse_line *line, int *i, int min, int max);
void	parse_check_vec3f(t_parse_line *line, t_vec3f *f, float min, float max);
void	parse_check_vec3i(t_parse_line *line, t_vec3i *i, int min, int max);
void	parse_check_color(t_parse_line *line, t_vec3f *color, int min, int max);
void	parse_check_char(t_parse_line *line, char *c, char *set);

int		trgb_to_int(int t, int r, int g, int b);
int		rgb_to_color(t_vec3i color);
int		float_to_color(float color);
t_vec3i	float_to_color_vec(t_vec3f color);
t_vec3f	ray_color(t_ray r, t_scene *scene);
int		ray_to_pixel_color(t_vec3f ray_colour);

t_vec3f	spot_light(t_vec3f pos, t_vec3f dir, t_scene *scene);
void	get_scene(char *filename, t_scene *scene);

float	hit_sphere(t_sphere sphere, t_ray r);
float	hit_plane(t_vec3f plane_dir, t_vec3f plane_pos, t_ray r);
float	hit_cylinder(t_cylinder cylinder, t_ray r, int *hit_side);
t_vec3f	cylinder_side_norm(t_vec3f hit_pos, t_cylinder cylinder);

t_vec3f	plane_normal(t_vec3f plane_dir, t_vec3f ray_dir);

void	init_mlx(t_scene *scene);
void	init_image(t_info *info);
int		handle_key(int keycode, void *param);
int		handle_destroy(void *param);
int		draw_to_window(t_info *info);
void	pixel_put_image(t_arr2di *image, int x, int y, int color);

t_vec3f	f_reflection(t_vec3f incoming, t_vec3f normal);
t_vec3f	get_normal_sphere(t_vec3f hit_point, t_vec3f sphere_center);
t_ray	rotate_ray(t_ray r, t_cylinder cylinder);
int		ray_in_right_dir(t_ray r, t_cylinder cylinder);
float	hit_top_or_bottom(t_ray ray, t_cylinder cylinder);
float	hit_infinite_cylinder(t_ray r, t_cylinder cylinder);
void	plane_loop(t_ray r, t_scene *scene, t_hits *hits);
void	sphere_loop(t_ray r, t_scene *scene, t_hits *hits);
void	cylinder_loop(t_ray r, t_scene *scene, t_hits *hits);
void	get_hit(t_hits *hit, t_scene *scene, t_ray r);

t_vec3f	get_sphere_norm_color(t_hits hit, t_ray r, \
	t_sphere *spheres, t_vec3f *norm_dir);
t_vec3f	get_plane_norm_color(t_hits hit, t_ray r, \
	t_plane *planes, t_vec3f *norm_dir);
t_vec3f	get_cylinder_norm_color(t_hits hit, t_ray r, \
	t_cylinder *cylinders, t_vec3f *norm_dir);

float	abc(float a, float b, float c, int *solved);
t_vec3f	ft_rodrigues(t_vec3f v, t_vec3f k, float angle);
float	signf(float a);
t_vec3f	at(t_ray r, float t);

void	error(char *str);
void	digit_error(t_parse_line *line);
#endif
