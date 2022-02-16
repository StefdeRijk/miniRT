#include "miniRT.h"

void	parse_check_int(t_parse_line *line, int *i, int min, int max)
{
	parse_int(line, i);
	check_range_i(line, *i, min, max);
}

void	parse_check_vec3i(t_parse_line *line, t_vec3i *i, int min, int max)
{
	parse_vec3i(line, i);
	check_range_vec3i(line, *i, min, max);
}

void	parse_check_char(t_parse_line *line, char *c, char *set)
{
	parse_char(line, c);
	check_in_set(line, c, set);
}

void	check_in_set(t_parse_line *line, char *c, char *set)
{
	if (!ft_strchr(set, *c))
	{
		printf("Expected char in \"%s\" at line %d, at column %d, found %c", \
		set, line->line_nr, line->i, *c);
		exit(1);
	}
}
