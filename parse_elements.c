#include "miniRT.h"

void	parse_check_color(t_parse_line *line, t_vec3f *color, int min, int max)
{
	t_vec3i	color_int;

	parse_check_vec3i(line, &color_int, min, max);
	*color = color_to_float_vec(color_int);
}

void	parse_ambient(t_parse_line *line, t_scene *scene)
{
	t_ambient	*a;

	if (scene->ambient)
		error("Found multiple ambient sources in file");
	scene->ambient = malloc(sizeof(*scene->ambient));
	a = scene->ambient;
	parse_check_float(line, &a->brightness, 0.0, 1.0);
	skip_one_or_more_char(line, ' ');
	parse_check_color(line, &a->color, 0, 255);
	skip_one_char(line, '\n');
}

void	parse_camera(t_parse_line *line, t_scene *scene)
{
	t_camera	*c;

	if (scene->camera)
		error("Found multiple camera sources in file");
	scene->camera = malloc(sizeof(*scene->camera));
	c = scene->camera;
	parse_vec3f(line, &c->pos);
	skip_one_or_more_char(line, ' ');
	parse_check_vec3f(line, &c->dir, -1, 1);
	skip_one_or_more_char(line, ' ');
	parse_check_float(line, &c->fov, 0, 180);
	skip_one_char(line, '\n');
}

void	parse_light(t_parse_line *line, t_scene *scene)
{
	t_light	*l;

	if (scene->light)
		error("Found multiple light sources in file");
	scene->light = malloc(sizeof(*scene->light));
	l = scene->light;
	parse_vec3f(line, &l->pos);
	skip_one_or_more_char(line, ' ');
	parse_check_float(line, &l->brightness, 0, 1);
	skip_one_or_more_char(line, ' ');
	parse_check_color(line, &l->color, 0, 255);
	skip_one_or_more_char(line, '\n');
}

void	parse_elem_type(t_parse_line *line, t_scene_elem_type *t)
{
	char	c;
	char	c2;

	c2 = 0;
	c = line->line[line->i];
	if (c)
		c2 = line->line[line->i + 1];
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
	else
	{
		printf("Expected element type at line %d, column %d, found '%c' (\n",
		line->line_nr, line->i, c);
		error("Parse error");
	}
	line->i++;
	if (*t == SPHERE || *t == PLANE || *t == CYLINDER)
		line->i++;
	skip_one_or_more_char(line, ' ');
}
