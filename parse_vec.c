/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_vec.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/06 11:25:34 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/06 11:25:34 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_vec3i(t_parse_line *line, t_vec3i *v)
{
	parse_int(line, &v->x);
	skip_one_char(line, ',');
	parse_int(line, &v->y);
	skip_one_char(line, ',');
	parse_int(line, &v->z);
}

void	parse_vec3f(t_parse_line *line, t_vec3f *v)
{
	parse_float(line, &v->x);
	skip_one_char(line, ',');
	parse_float(line, &v->y);
	skip_one_char(line, ',');
	parse_float(line, &v->z);
}
