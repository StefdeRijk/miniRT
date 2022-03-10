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
		printf("Expected '%c' (as number: %d) at line %d, \
		column %d, found '%c' (as number: %d) \n", \
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

void	parse_string(t_parse_line *line, char *buffer, int size)
{
	int	i;
	char	c;

	c = line->line[line->i];
	i = 0;
	while (c && c != ' ' && c != '\n')
	{
		if (i >= size)
		{
			printf("String too long at line %d, \
					column %d\n", line->line_nr, line->i);
			error("Parse error");
		}
		buffer[i] = c;
		c = line_next(line);
		i++;
	}
	buffer[i] = 0;
}
