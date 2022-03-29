#include "miniRT.h"

void	set_element(t_parse_line *line, char c, char c2, t_scene_elem_type *t)
{
	if (c == 'A')
		*t = AMBIENT;
	else if (c == 'C')
		*t = CAMERA;
	else if (c == 'L')
		*t = LIGHT;
	else if (c == 's' && c2 == 'p')
		*t = SPHERE;
	else if (c == 'p' && c2 == 'l')
		*t = PLANE;
	else if (c == 'c' && c2 == 'y')
		*t = CYLINDER;
	else if (BONUS && c == 'p' && c2 == 'a')
		*t = PARABOLOID;
	else
	{
		printf("Expected element type at line %d, column %d, found '%c' (\n",
			line->line_nr, line->i + 1, c);
		error("Parse error");
	}
}

void	parse_elem_type(t_parse_line *line, t_scene_elem_type *t)
{
	char	c;
	char	c2;

	c2 = 0;
	c = line->line[line->i];
	if (c)
		c2 = line->line[line->i + 1];
	set_element(line, c, c2, t);
	line->i++;
	if (*t == SPHERE || *t == PLANE || *t == CYLINDER || *t == PARABOLOID)
		line->i++;
	skip_one_or_more_char(line, ' ');
}
