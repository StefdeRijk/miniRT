#ifndef VEC_H
# define VEC_H

typedef enum e_direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
}	t_direction;

typedef struct s_vec {
	void	*data;
	int		len;
	int		cap;
	int		elem_size;
}	t_vec;

typedef struct s_vec3i {
	union {
		int	x;
		int	r;
	};
	union {
		int	y;
		int	g;
	};
	union {
		int	z;
		int	b;
	};
}	t_vec3i;

typedef struct s_vec3f {
	float	x;
	float	y;
	float	z;
}	t_vec3f;

typedef struct s_vec2i {
	int	x;
	int	y;
}	t_vec2i;

typedef struct s_vec2f {
	float	x;
	float	y;
}	t_vec2f;

typedef struct s_line3f {
	t_vec3f	p1;
	t_vec3f	p2;
}	t_line3f;

typedef struct s_line2f {
	t_vec2f	p1;
	t_vec2f	p2;
}	t_line2f;

void		vec_init(t_vec *vec, int elem_size);
void		vec_print(t_vec *vec);
void		vec_pop_n(t_vec *vec, int i, int n);
void		vec_push(t_vec *vec, void *i);
void		vec_push_n(t_vec *vec, void *i, int n);

t_vec2f		vec2f_add(t_vec2f v1, t_vec2f v2);

t_vec3f		vec3f_init(float x, float y, float z);
t_vec3f 	vec3f_div(t_vec3f v, float f);
t_vec3f		vec3f_mul(t_vec3f v, float f);
t_vec3f		vec3f_sub(t_vec3f v1, t_vec3f v2);
t_vec3f		vec3f_add(t_vec3f v1, t_vec3f v2);
t_vec3f		vec3f_unit(t_vec3f v);
float		vec3f_len(t_vec3f v);
float		vec3f_len_sq(t_vec3f v);
float		vec3f_dot(t_vec3f v1, t_vec3f v2);

t_vec2i		vec2i_trans(t_vec2i v, t_direction dir);

t_vec3i		vec3i_init(int x, int y, int z);

t_line3f	make_line3f(t_vec3f p1, t_vec3f p2);
t_line2f	make_line2f(t_vec2f p1, t_vec2f p2);

int			gradient_to_color(t_vec2i gradient, float grad_level);
void		vec_free(t_vec vec);

#endif
