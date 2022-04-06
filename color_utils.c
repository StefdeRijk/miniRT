/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/06 11:25:31 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/06 11:25:31 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	trgb_to_int(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

float	tone_mapping(float i)
{
	return (i / (i + 1.));
}

float	color_to_float(int color)
{
	return ((float)color / 255.);
}

int	float_to_color(float color)
{
	return (tone_mapping(color) * 255.);
}

int	vec_to_color(t_vec3f v)
{
	return (trgb_to_int(0, v.x * 255, v.y * 255,
			v.z * 255));
}
