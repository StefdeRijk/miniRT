#include "miniRT.h"

void	parse_check_float_exc(t_parse_line *line, float *f, float min,
		float max)
{
	parse_float(line, f);
	check_range_f_exc(line, *f, min, max);
}

void	parse_check_float_pos(t_parse_line *line, float *f)
{
	parse_float(line, f);
	check_positive_f(line, *f);
}

void	parse_check_float(t_parse_line *line, float *f, float min, float max)
{
	parse_float(line, f);
	check_range_f(line, *f, min, max);
}

void	parse_check_vec3f(t_parse_line *line, t_vec3f *f, float min, float max)
{
	parse_vec3f(line, f);
	check_range_vec3f(line, *f, min, max);
}
