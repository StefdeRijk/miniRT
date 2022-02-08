#include "miniRT.h"

void	parse_check_float(t_parse_line *line, float *f, float min, float max)
{
	parse_float(line, f);
	check_range_f(line, *f, min, max);
}

void	parse_check_int(t_parse_line *line, int *i, int min, int max)
{
	parse_int(line, i);
	check_range_i(line, *i, min, max);
}

void	parse_check_vec3f(t_parse_line *line, t_vec3f *f, float min, float max)
{
	parse_vec3f(line, f);
	check_range_vec3f(line, *f, min, max);
}

void	parse_check_vec3i(t_parse_line *line, t_vec3i *i, int min, int max)
{
	parse_vec3i(line, i);
	check_range_vec3i(line, *i, min, max);
}
