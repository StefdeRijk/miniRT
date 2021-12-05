#include "miniRT.h"


void	parse_line(t_parse_line line, t_scene *scene)
{
	t_scene_elem_type		et;
	static t_elem_parser	parse_elem[NR_ELEM_TYPES] =
	{
		parse_ambient,
		parse_camera,
		parse_light,
		parse_sphere,
		parse_plane,
		parse_cylinder,
	};
	parse_elem_type(&line, &et);
	skip_one_or_more_char(&line, ' ');
	parse_elem[et](&line, scene);
}

void	get_scene(char *filename, t_scene *scene)
{
	int				fd;
	t_parse_line	line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error("Could not open file");
	line.line = get_next_line(fd);
	line.line_nr = 0;
	while (line.line)
	{
		line.i = 0;
		parse_line(line, scene);
		free(line.line);
		line.line = get_next_line(fd);
		line.line_nr++;
	}
}

void	error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	check_args(int argc, char **argv)
{
	int	filename_len;

	if (argc != 2)
		error("miniRT accepts exaclty one argument");
	filename_len = ft_strlen(argv[1]);
	if (filename_len < 3
		|| ft_strcmp(argv[1] + filename_len - 3, ".rt"))
		error("filename should end in .rt");
}

int	main(int argc, char **argv)
{
	static t_scene	scene = {0};

	check_args(argc, argv);
	get_scene(argv[1], &scene);
}
