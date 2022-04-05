/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec2i.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:42:33 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:42:33 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec2i	vec2i_trans(t_vec2i v, t_direction dir)
{
	t_vec2i	vr;

	vr = v;
	if (dir == UP)
		vr.y--;
	if (dir == DOWN)
		vr.y++;
	if (dir == LEFT)
		vr.x--;
	if (dir == RIGHT)
		vr.x++;
	return (vr);
}
