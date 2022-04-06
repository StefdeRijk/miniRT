/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_positive.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/06 11:25:30 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/06 11:25:30 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_positive_f(t_parse_line *line, float f)
{
	if (f <= 0)
	{
		printf(
			"Expected positive float at line %d "
			", column %d, found %f\n", line->line_nr, line->i + 1, f);
		error("Float not in range");
	}
}
