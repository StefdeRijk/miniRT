#include "miniRT.h"
#include <pthread.h>

#define THREADS 4

t_vec3f	get_ray_direction(t_info *info, int i, int j, t_vec3f camera)
{
	float	u;
	float	v;
	t_vec3f	hor_offset;
	t_vec3f	ver_offset;
	t_vec3f	direction;

	u = (float)i / (WIN_WIDTH - 1);
	v = (float)j / (info->win_height - 1);
	hor_offset = vec3f_mul(info->horizontal, u);
	ver_offset = vec3f_mul(info->vertical, v);
	direction = vec3f_add(info->lower_left_corner, hor_offset);
	direction = vec3f_add(direction, ver_offset);
	direction = vec3f_sub(direction, camera);
	return (vec3f_unit(direction));
}

t_vec3f	shoot_rays(int i, int j, t_info *info, t_scene *scene)
{
	t_vec3f	direction;
	t_ray	r;

	direction = get_ray_direction(info, i, j, scene->camera->pos);
	r.origin = scene->camera->pos;
	r.dir = direction;
	r.bounces = 0;
	return (ray_color(r, scene));
}

void	*paint_pixels(void *thread_data_p)
{
	int						x;
	int						y;
	t_vec3f					ray_colour;
	struct s_thread_data	*thread_data;
	int						next_pixel;

	thread_data = (struct s_thread_data *)thread_data_p;
	while (1)
	{
		pthread_mutex_lock(&thread_data->pixel_mutex);
		next_pixel = thread_data->next_pixel;
		thread_data->next_pixel++;
		pthread_mutex_unlock(&thread_data->pixel_mutex);
		if (next_pixel >= thread_data->info->win_height * WIN_WIDTH)
			break ;
		x = next_pixel % WIN_WIDTH;
		y = next_pixel / WIN_WIDTH;
		ray_colour = shoot_rays(x, y, thread_data->info, thread_data->scene);
		pixel_put_image(&thread_data->info->img, x, \
			thread_data->info->win_height - y - 1, \
			ray_to_pixel_color(ray_colour));
	}
	return (NULL);
}

void	paint_img(t_info *info, t_scene *scene)
{
	int						err;
	pthread_t				thread[THREADS];
	struct s_thread_data	thread_data;
	int						i;

	thread_data.info = info;
	thread_data.scene = scene;
	thread_data.next_pixel = 0;
	if (pthread_mutex_init(&thread_data.pixel_mutex, NULL))
		error("could not create mutex");
	i = 0;
	while (i < THREADS)
	{
		err = pthread_create(&thread[i], NULL, paint_pixels, &thread_data);
		if (err)
			error("thread creation failed");
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}
