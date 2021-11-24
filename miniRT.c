#include "miniRT.h"

void	error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit(1);
}

void	check_args(int argc, char **argv)
{
	int	filename_len;

	if (argc != 2)
		error("miniRT accepts exaclty one argument\n");
	filename_len = ft_strlen(argv[1]);
	if (filename_len < 3
		|| ft_strcmp(argv[1] + filename_len - 3, ".rt"))
		error("filename should end in .rt\n");
}

int	main(int argc, char **argv)
{
	check_args(argc, argv);



}
