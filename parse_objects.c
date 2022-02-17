#include "miniRT.h"

void	parse_sphere(t_parse_line *line, t_scene *scene)
{
	t_sphere	s;
	char		material;

	if (!scene->spheres.data)
		vec_init(&scene->spheres, sizeof(t_sphere));
	parse_vec3f(line, &s.pos);
	skip_one_or_more_char(line, ' ');
	parse_float(line, &s.radius);
	s.radius /= 2;
	skip_one_or_more_char(line, ' ');
	parse_check_color(line, &s.color, 0, 255);
	if (BONUS)
	{
		skip_one_or_more_char(line, ' ');
		parse_check_char(line, &material, "cnmg");
		if (material == 'c')
			s.material = CHECKER;
		if (material == 'n')
			s.material = NORMAL;
		if (material == 'm')
			s.material = MIRROR;
		if (material == 'g')
			s.material = GLASS;
	}
	skip_one_or_more_char(line, '\n');
	vec_push(&scene->spheres, &s);
}

void	parse_plane(t_parse_line *line, t_scene *scene)
{
	t_plane	p;

	if (!scene->planes.data)
		vec_init(&scene->planes, sizeof(t_plane));
	parse_vec3f(line, &p.pos);
	skip_one_or_more_char(line, ' ');
	parse_check_vec3f(line, &p.dir, -1, 1);
	if (vec3f_len_sq(p.dir) == 0)
	{
		printf("Plane direction at line %d is a null vector, "
			"cannot be normalized.", line->line_nr);
		exit(1);
	}
	p.dir = vec3f_unit(p.dir);
	skip_one_or_more_char(line, ' ');
	parse_check_color(line, &p.color, 0, 255);
	skip_one_or_more_char(line, '\n');
	vec_push(&scene->planes, &p);
}

void	parse_cylinder(t_parse_line *line, t_scene *scene)
{
	t_cylinder	c;

	if (!scene->cylinders.data)
		vec_init(&scene->cylinders, sizeof(t_cylinder));
	parse_vec3f(line, &c.pos);
	skip_one_or_more_char(line, ' ');
	parse_check_vec3f(line, &c.dir, -1, 1);
	skip_one_or_more_char(line, ' ');
	parse_float(line, &c.radius);
	c.radius /= 2;
	skip_one_or_more_char(line, ' ');
	parse_float(line, &c.height);
	skip_one_or_more_char(line, ' ');
	parse_check_color(line, &c.color, 0, 255);
	skip_one_or_more_char(line, '\n');
	if (vec3f_len_sq(c.dir) == 0)
	{
		printf("Cylinder direction at line %d is a null vector, "
			"cannot be normalized.", line->line_nr);
		exit(1);
	}
	c.dir = vec3f_unit(c.dir);
	vec_push(&scene->cylinders, &c);
}
