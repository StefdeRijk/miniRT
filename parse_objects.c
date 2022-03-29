#include "miniRT.h"

t_material_type	parse_check_material(t_parse_line *line)
{
	char		material;

	skip_one_or_more_char(line, ' ');
	parse_check_char(line, &material, "cnm");
	if (material == 'c')
		return (CHECKER);
	else if (material == 'n')
		return (NORMAL);
	else
		return (MIRROR);
}

void	parse_sphere(t_parse_line *line, t_scene *scene)
{
	t_object	o;
	t_sphere	*s;

	s = &o.sphere;
	parse_vec3f(line, &s->base.pos);
	skip_one_or_more_char(line, ' ');
	parse_float(line, &s->radius);
	s->radius /= 2;
	skip_one_or_more_char(line, ' ');
	parse_check_color(line, &s->base.color, 0, 255);
	if (BONUS)
	{
		s->base.material = parse_check_material(line);
		parse_texture(&s->base.texture, line);
		parse_texture(&s->base.bump_map, line);
	}
	skip_one_or_more_char(line, '\n');
	s->base.get_color = get_sphere_color;
	s->base.get_normal = get_sphere_normal;
	s->base.type = SPHERE;
	vec_push(&scene->objects, &o);
}

void	parse_plane(t_parse_line *line, t_scene *scene)
{
	t_object	o;
	t_plane		*p;

	p = &o.plane;
	parse_vec3f(line, &p->dir_base.base.pos);
	skip_one_or_more_char(line, ' ');
	parse_check_vec3f(line, &p->dir_base.dir, -1, 1);
	if (vec3f_len_sq(p->dir_base.dir) == 0)
	{
		printf("Plane direction at line %d is a null vector, "
			"cannot be normalized.", line->line_nr);
		exit(1);
	}
	p->dir_base.dir = vec3f_unit(p->dir_base.dir);
	skip_one_or_more_char(line, ' ');
	parse_check_color(line, &p->dir_base.base.color, 0, 255);
	if (BONUS)
	{
		p->dir_base.base.material = parse_check_material(line);
		parse_texture(&p->dir_base.base.texture, line);
		parse_texture(&p->dir_base.base.bump_map, line);
	}
	skip_one_or_more_char(line, '\n');
	p->dir_base.base.type = PLANE;
	p->dir_base.base.get_color = get_plane_color;
	p->dir_base.base.get_normal = get_plane_normal;
	vec_push(&scene->objects, &o);
}

void	parse_cylinder(t_parse_line *line, t_scene *scene)
{
	t_object	o;
	t_cylinder	*c;

	c = &o.cylinder;
	parse_vec3f(line, &c->dir_base.base.pos);
	skip_one_or_more_char(line, ' ');
	parse_check_vec3f(line, &c->dir_base.dir, -1, 1);
	skip_one_or_more_char(line, ' ');
	parse_float(line, &c->radius);
	c->radius /= 2;
	skip_one_or_more_char(line, ' ');
	parse_float(line, &c->height);
	skip_one_or_more_char(line, ' ');
	parse_check_color(line, &c->dir_base.base.color, 0, 255);
	if (BONUS)
		c->dir_base.base.material = parse_check_material(line);
	skip_one_or_more_char(line, '\n');
	if (vec3f_len_sq(c->dir_base.dir) == 0)
	{
		printf("Cylinder direction at line %d is a null vector, "
			"cannot be normalized.", line->line_nr);
		exit(1);
	}
	c->dir_base.dir = vec3f_unit(c->dir_base.dir);
	c->dir_base.base.type = CYLINDER;
	c->dir_base.base.get_color = get_cylinder_color;
	c->dir_base.base.get_normal = get_cylinder_normal;
	vec_push(&scene->objects, &o);
}

void	parse_paraboloid(t_parse_line *line, t_scene *scene)
{
	t_object		o;
	t_paraboloid	*p;

	p = &o.paraboloid;
	parse_vec3f(line, &p->dir_base.base.pos);
	skip_one_or_more_char(line, ' ');
	parse_check_vec3f(line, &p->dir_base.dir, -1, 1);
	if (vec3f_len_sq(p->dir_base.dir) == 0)
	{
		printf("Paraboloid direction at line %d is a null vector, "
			"cannot be normalized.", line->line_nr);
		exit(1);
	}
	p->dir_base.dir = vec3f_unit(p->dir_base.dir);
	skip_one_or_more_char(line, ' ');
	parse_float(line, &p->curvature);
	skip_one_or_more_char(line, ' ');
	parse_check_color(line, &p->dir_base.base.color, 0, 255);
	p->dir_base.base.material = parse_check_material(line);
	skip_one_or_more_char(line, '\n');
	p->dir_base.base.type = PARABOLOID;
	p->dir_base.base.get_color = get_paraboloid_color;
	p->dir_base.base.get_normal = get_paraboloid_normal;
	vec_push(&scene->objects, &o);
}
