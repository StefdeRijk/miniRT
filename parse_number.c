#include "miniRT.h"
#include <limits.h>
#include <float.h>

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
		if (l > INT_MAX || l < INT_MIN)
		{
			if (l > INT_MAX)
				printf("Integer too large at line %d, column %d.",
						line->line_nr, line->i + 1);
			if (l < INT_MIN)
				printf("Integer too small at line %d, column %d.",
						line->line_nr, line->i + 1);
			error("Parse error");
		}
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
		if (d > FLT_MAX || d < -FLT_MAX)
		{
			if (d > FLT_MAX)
				printf("Float too large at line %d, column %d.",
						line->line_nr, line->i + 1);
			if (d < -FLT_MAX)
				printf("Float too small at line %d, column %d.",
						line->line_nr, line->i + 1);
			error("Parse error");
		}
	}
	if (c == '.')
		parse_decimals(line, &d, sign);
	*f = d;
}
