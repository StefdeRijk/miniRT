#include "vec.h"

t_line3f	make_line3f(t_vec3f p1, t_vec3f p2)
{
	t_line3f	line;

	line.p1 = p1;
	line.p2 = p2;
	return (line);
}

t_line2f	make_line2f(t_vec2f p1, t_vec2f p2)
{
	t_line2f	line;

	line.p1 = p1;
	line.p2 = p2;
	return (line);
}
