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
