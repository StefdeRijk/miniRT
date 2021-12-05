#include "miniRT.h"

void	digit_error(t_parse_line *line)
{
	printf("Expected digit at line %d, column %d, found '%c'\n",
		line->line_nr, line->i, line->line[line->i]);
	error("Parse error");
}

void	parse_int(t_parse_line *line, int *i)
{
	int		sign;
	char	c;

	*i = 0;
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
		*i = *i * 10 + sign * (c - '0');
		c = line_next(line);
	}
}

void	parse_float(t_parse_line *line, float *f)
{
	float	sign;
	char	c;
	float	after_dot;
	float	after_dot_mul;

	*f = 0;
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
		*f = *f * 10 + sign * (c - '0');
		c = line_next(line);
	}
	if (c == '.')
	{
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
}
