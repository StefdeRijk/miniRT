#include "miniRT.h"

char	line_next(t_parse_line *line)
{
	line->i++;
	return (line->line[line->i]);
}

void	skip_one_char(t_parse_line *line, char c)
{
	if (line->line[line->i] != c)
	{
		printf("Expected '%c' (as number: %d) at line %d, column %d, found '%c' (as number: %d) \n",
			c, c, line->line_nr, line->i, line->line[line->i], line->line[line->i]);
		error("Parse error");
	}
	line->i++;
}

void	skip_zero_or_more_char(t_parse_line *line, char c)
{
	while (line->line[line->i] == c)
		line->i++;
}

void	skip_one_or_more_char(t_parse_line *line, char c)
{
	skip_one_char(line, c);
	skip_zero_or_more_char(line, c);
}
