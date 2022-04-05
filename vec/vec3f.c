/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec3f.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:42:33 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:42:33 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include <math.h>
#include <stdio.h>

t_vec3f	vec3f_init(float x, float y, float z)
{
	t_vec3f	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

void	vec3f_print(t_vec3f v)
{
	printf("(%f, %f, %f)\n", v.x, v.y, v.z);
}

t_vec3f	vec3f_trans(t_vec3f v, t_direction dir, float distance)
{
	if (dir == UP)
	{
		v.x = v.x;
		v.y = v.y - distance;
	}
	if (dir == DOWN)
	{
		v.x = v.x;
		v.y = v.y + distance;
	}
	if (dir == LEFT)
	{
		v.x = v.x - distance;
		v.y = v.y;
	}
	if (dir == RIGHT)
	{
		v.x = v.x + distance;
		v.y = v.y;
	}
	return (v);
}

t_vec3f	vec3f_unit(t_vec3f v)
{
	return (vec3f_mul(v, 1 / vec3f_len(v)));
}

float	vec3f_dist(t_vec3f v1, t_vec3f v2)
{
	return (vec3f_len(vec3f_sub(v1, v2)));
}
