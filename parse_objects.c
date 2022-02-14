#include "miniRT.h"

void	parse_sphere(t_parse_line *line, t_scene *scene)
{
	t_sphere	s;

	if (!scene->spheres.data)
		vec_init(&scene->spheres, sizeof(t_sphere));
	parse_vec3f(line, &s.pos);
	skip_one_or_more_char(line, ' ');
	parse_float(line, &s.radius);
	s.radius /= 2;
	skip_one_or_more_char(line, ' ');
	parse_check_color(line, &s.color, 0, 255);
	// smooth and matt objects
	// skip_one_or_more_char(line, ' ');
	// parse_check_char(line, &s.material, "ms");
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
	skip_one_or_more_char(line, ' ');
	parse_check_color(line, &p.color, 0, 255);
	// smooth and matt objects
	// skip_one_or_more_char(line, ' ');
	// parse_check_char(line, &p.material, "ms");
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
	parse_float(line, &c.diameter);
	skip_one_or_more_char(line, ' ');
	parse_float(line, &c.height);
	skip_one_or_more_char(line, ' ');
	parse_check_color(line, &c.color, 0, 255);
	// smooth and matt objects
	// skip_one_or_more_char(line, ' ');
	// parse_check_char(line, &c.material, "ms");
	skip_one_or_more_char(line, '\n');
	vec_push(&scene->cylinders, &c);
}
