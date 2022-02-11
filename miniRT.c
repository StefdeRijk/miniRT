#include "miniRT.h"

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
	static t_scene	scene = {};

	check_args(argc, argv);
	get_scene(argv[1], &scene);
	init_mlx(&scene);
}
