#include "miniRT.h"
#include <stdlib.h>
#include <stdio.h>

void	check_magic(uint16_t file_type, char *file)
{
	if (file_type != 0x4D42)
	{
		printf("file %s\n", file);
		error("no bmp!");
	}
}
