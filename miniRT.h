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
	float	diameter;
	float	height;
	t_vec3f	color;
	char	material;
}	t_cylinder;

typedef struct s_scene {
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_vec		spheres;
	t_vec		planes;
	t_vec		cylinders;
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

typedef enum e_scene_elem_type {
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	NR_ELEM_TYPES
}	t_scene_elem_type;

typedef struct s_parse_line {
	char	*line;
	int		i;
	int		line_nr;
}	t_parse_line;

typedef void	(*t_elem_parser)(t_parse_line *line, t_scene *scene);
void	error(char *str);
char	line_next(t_parse_line *line);
void	skip_one_char(t_parse_line *line, char c);
void	skip_zero_or_more_char(t_parse_line *line, char c);
void	skip_one_or_more_char(t_parse_line *line, char c);
void	parse_elem_type(t_parse_line *line, t_scene_elem_type *t);
void	parse_ambient(t_parse_line *line, t_scene *scene);
void	parse_camera(t_parse_line *line, t_scene *scene);
void	parse_light(t_parse_line *line, t_scene *scene);
void	parse_sphere(t_parse_line *line, t_scene *scene);
void	parse_plane(t_parse_line *line, t_scene *scene);
void	parse_cylinder(t_parse_line *line, t_scene *scene);
void	parse_line(t_parse_line line, t_scene *scene);
void	digit_error(t_parse_line *line);
void	parse_int(t_parse_line *line, int *i);
void	parse_float(t_parse_line *line, float *f);
void	parse_vec3i(t_parse_line *line, t_vec3i *v);
void	parse_vec3f(t_parse_line *line, t_vec3f *v);
char	line_next(t_parse_line *line);
void	check_range_f(t_parse_line *line, float f, float min, float max);
void	check_range_vec3f(t_parse_line *line, t_vec3f v, float min, float max);
void	check_range_i(t_parse_line *line, int i, int min, int max);
void	check_range_vec3i(t_parse_line *line, t_vec3i v, int min, int max);
void	check_range_f_exc(t_parse_line *line, float f, float min, float max);
void	parse_check_float(t_parse_line *line, float *f, float min, float max);
void	parse_check_float_exc(t_parse_line *line, float *f, float min, float max);
void	parse_check_int(t_parse_line *line, int *i, int min, int max);
void	parse_check_vec3f(t_parse_line *line, t_vec3f *f, float min, float max);
void	parse_check_vec3i(t_parse_line *line, t_vec3i *i, int min, int max);
int		rgb_to_color(t_vec3i color);
int		trgb_to_int(int t, int r, int g, int b);
float	hit_sphere(t_sphere sphere, t_ray r);
t_vec3f	ray_color(t_ray r, t_scene *scene);
void	parse_check_color(t_parse_line *line, t_vec3f *color, int min, int max);
t_vec3i	float_to_color_vec(t_vec3f color);
int		float_to_color(float color);
t_vec3f spot_light(t_ray r, t_scene *scene);
float   hit_plane(t_plane plane, t_ray r);
void	parse_check_char(t_parse_line *line, char *c, char *set);
void	parse_char(t_parse_line *line, char *c);
void	check_in_set(t_parse_line *line, char *c, char *set);
void	get_scene(char *filename, t_scene *scene);
void	parse_line(t_parse_line line, t_scene *scene);

void	init_mlx(t_scene *scene);
void	error(char *str);

t_vec3f	f_reflection(t_vec3f incoming, t_vec3f normal);
t_vec3f	get_normal_sphere(t_vec3f hit_point, t_vec3f sphere_center);
t_vec3f	at(t_ray r, float t);
int		sphere_to_pixel_color(t_vec3f ray_colour);
#endif
