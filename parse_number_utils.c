#include "miniRT.h"
#include <limits.h>
#include <float.h>

void	check_long_over_int(long l, t_parse_line *line)
{
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

void	check_double_over_float(double d, t_parse_line *line)
{
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
