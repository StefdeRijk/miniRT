#include "miniRT.h"
void	check_range_f(t_parse_line *line, float f, float min, float max)
{
	if (f < min || f > max)
	{
		ft_printf("Expected float between %fat line %d, column %d, found %c",
			line->line_nr, line->i, line->line[line->i]);


}
