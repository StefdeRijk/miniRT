#include "miniRT.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	open_file_to_write(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY);
	if (fd == -1)
	{
		printf("%s\n", file);
		error("file not found");
	}
	return (fd);
}

t_bmp	scale_bmp(char *file, float scale)
{
	struct s_BMPFileHeader	header;
	struct s_BMPInfoHeader	infoheader;
	int						fd;
	t_bmp					image;
	int						skip;
	char 					skip_buffer[1000];

	fd = open_file(file);
	checked_read(fd, &header, sizeof(header));
	if (header.file_type != 0x4D42)
	{
		printf("file %s\n", file);
		error("no bmp!");
	}
	checked_read(fd, &infoheader, sizeof(infoheader));
	init_bmp_image(&image, infoheader);
	skip = header.offset_data - sizeof(header) - sizeof(infoheader);
	if (skip < 0)
		error("file corrupted!");
	checked_read(fd, skip_buffer, skip);
	image.data = ft_malloc_or_exit(image.bytes_per_row * image.height * \
		sizeof(char));
	checked_read(fd, image.data, \
		image.bytes_per_row * image.height * sizeof(char));
	for (int y = 0; y < image.height; y++)
		for (int x = 0; x < image.width; x++) 
		{
			int old_val = image.data[x * image.bytes_per_pixel + y *image.bytes_per_row + 1];
			old_val -= 128;
			old_val *= scale;
			old_val += 128;
			image.data[x * image.bytes_per_pixel + y *image.bytes_per_row + 1] = old_val;
			old_val = image.data[x * image.bytes_per_pixel + y *image.bytes_per_row + 2];
			old_val -= 128;
			old_val *= scale;
			old_val += 128;
			image.data[x * image.bytes_per_pixel + y *image.bytes_per_row + 2] = old_val;
		}
	close(fd);
	fd = open_file_to_write("scale_test.bmp");
	printf("file type header: %x\n", header.file_type);
	write(fd, &header, sizeof(header));
	write(fd, &infoheader, sizeof(infoheader));
	skip = header.offset_data - sizeof(header) - sizeof(infoheader);
	write(fd, skip_buffer, skip);
	write(fd, image.data, sizeof(char) * image.bytes_per_row * image.height);
	return (image);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	scale_bmp("water_normal.bmp", 0.5);
	return (0);
}
