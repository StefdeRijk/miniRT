#include "miniRT.h"

t_material_type	parse_check_material(t_parse_line *line)
{
	char		material;

	skip_one_or_more_char(line, ' ');
	parse_check_char(line, &material, "cnmg");
	if (material == 'c')
		return (CHECKER);
	if (material == 'n')
		return (NORMAL);
	if (material == 'm')
		return (MIRROR);
	else
		return (GLASS);
}

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
	if (BONUS)
	{
		s.material = parse_check_material(line);
		skip_zero_or_more_char(line, ' ');
		parse_string(line, s.texture.filename, MAX_TEXTURE_FILE_SIZE);
		if (s.texture.filename[0])
			s.texture = read_bmp(s.texture.filename);
		skip_zero_or_more_char(line, ' ');
		parse_string(line, s.bump_map.filename, MAX_TEXTURE_FILE_SIZE);
		if (s.bump_map.filename[0])
			s.bump_map = read_bmp(s.bump_map.filename);
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
	if (BONUS)
	{
		p.material = parse_check_material(line);
		skip_zero_or_more_char(line, ' ');
		parse_string(line, p.texture.filename, MAX_TEXTURE_FILE_SIZE);
		if (p.texture.filename[0])
			p.texture = read_bmp(p.texture.filename);
		skip_zero_or_more_char(line, ' ');
		parse_string(line, p.bump_map.filename, MAX_TEXTURE_FILE_SIZE);
		if (p.bump_map.filename[0])
			p.bump_map = read_bmp(p.bump_map.filename);
	}
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
	if (BONUS)
		c.material = parse_check_material(line);
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

void	parse_paraboloid(t_parse_line *line, t_scene *scene)
{
	t_paraboloid	p;

	if (!scene->paraboloids.data)
		vec_init(&scene->paraboloids, sizeof(t_paraboloid));
	parse_vec3f(line, &p.pos);
	skip_one_or_more_char(line, ' ');
	parse_check_vec3f(line, &p.dir, -1, 1);
	if (vec3f_len_sq(p.dir) == 0)
	{
		printf("Paraboloid direction at line %d is a null vector, "
			"cannot be normalized.", line->line_nr);
		exit(1);
	}
	p.dir = vec3f_unit(p.dir);
	skip_one_or_more_char(line, ' ');
	parse_float(line, &p.curvature);
	skip_one_or_more_char(line, ' ');
	parse_check_color(line, &p.color, 0, 255);
	p.material = parse_check_material(line);
	skip_one_or_more_char(line, '\n');
	vec_push(&scene->paraboloids, &p);
}

