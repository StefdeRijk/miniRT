#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "stdlib.h"
# include "vec/vec.h"

typedef struct s_ambient {
	float	brightness;
	t_vec3i	color;
} t_ambient;

typedef struct s_camera {
	t_vec3f	pos;
	t_vec3f	dir;
	float	fov;
} t_camera;

typedef struct s_scene {
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
} t_scene;

}	t_scene;

#endif
