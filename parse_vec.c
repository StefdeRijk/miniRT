#include "miniRT.h"

void	parse_vec3i(t_parse_line *line, t_vec3i *v)
{
	parse_int(line, &v->x);
	skip_one_char(line, ',');
	parse_int(line, &v->y);
	skip_one_char(line, ',');
	parse_int(line, &v->z);
}

void	parse_vec3f(t_parse_line *line, t_vec3f *v)
{
	parse_float(line, &v->x);
	skip_one_char(line, ',');
	parse_float(line, &v->y);
	skip_one_char(line, ',');
	parse_float(line, &v->z);
}
