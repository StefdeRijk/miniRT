/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_number.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/06 11:25:33 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/06 11:25:33 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	digit_error(t_parse_line *line)
{
	printf("Expected digit at line %d, column %d, found '%c'\n",
		line->line_nr, line->i + 1, line->line[line->i]);
	error("Parse error");
}

void	parse_char(t_parse_line *line, char *c)
{
	*c = line->line[line->i];
	line->i++;
}

void	parse_int(t_parse_line *line, int *i)
{
	int		sign;
	char	c;
	long	l;

	l = 0;
	sign = 1;
	c = line->line[line->i];
	if (c == '-')
		sign = -1;
	if (c == '-' || c == '+')
		c = line_next(line);
	if (!ft_isdigit(c))
		digit_error(line);
	while (ft_isdigit(c))
	{
		l = l * 10 + sign * (c - '0');
		c = line_next(line);
		check_long_over_int(l, line);
	}
	*i = l;
}

void	parse_decimals(t_parse_line *line, double *f, float sign)
{
	char	c;
	float	after_dot;
	float	after_dot_mul;

	c = line_next(line);
	after_dot = 0;
	after_dot_mul = sign;
	while (ft_isdigit(c))
	{
		after_dot_mul /= 10;
		after_dot = after_dot * 10 + (c - '0');
		c = line_next(line);
	}
	*f += after_dot * after_dot_mul;
}

void	parse_float(t_parse_line *line, float *f)
{
	float	sign;
	char	c;
	double	d;

	d = 0;
	sign = 1;
	c = line->line[line->i];
	if (c == '-')
		sign = -1;
	if (c == '-' || c == '+')
		c = line_next(line);
	if (!ft_isdigit(c) && !(c == '.' && ft_isdigit(line->line[line->i + 1])))
		digit_error(line);
	while (ft_isdigit(c))
	{
		d = d * 10 + sign * (c - '0');
		c = line_next(line);
		check_double_over_float(d, line);
	}
	if (c == '.')
		parse_decimals(line, &d, sign);
	*f = d;
}
