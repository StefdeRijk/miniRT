#include "miniRT.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct	__attribute__((packed)) s_BMPFileHeader
{
	uint16_t	file_type;
	uint32_t	file_size;
	uint16_t	reserved1;
	uint16_t	reserved2;
	uint32_t	offset_data;
};

struct	__attribute__((packed)) s_BMPInfoHeader {
	uint32_t	size;
	int32_t		width;
	int32_t		height;
	uint16_t	planes;
	uint16_t	bit_count;
	uint32_t	compression;
	uint32_t	size_image;
	int32_t		x_pixels_per_meter;
	int32_t		y_pixels_per_meter;
	uint32_t	colors_used;
	uint32_t	colors_important;
};

static void	checked_read(int fd, void *buffer, long size)
{
	if (read(fd, buffer, size) != size)
		error("read error");
}

static void	bgr_to_rgb(unsigned char *image, uint32_t size, int bytes_per_pixel)
{
	uint32_t		i;
	unsigned char	tmp;

	i = 0;
	while (i < size)
	{
		tmp = image[i];
		image[i] = image[i + 2];
		image[i + 2] = tmp;
		i += bytes_per_pixel;
	}
}

void	init_bmp_image(t_bmp *image, struct s_BMPInfoHeader infoheader)
{
	image->width = infoheader.width;
	image->height = abs(infoheader.height);
	image->bytes_per_pixel = infoheader.bit_count / 8;
	image->bytes_per_row = image->width * image->bytes_per_pixel;
	if (image->bytes_per_row % 4)
		image->bytes_per_row += 4 - image->bytes_per_row % 4;
}

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("%s\n", file);
		error("file not found");
	}
	return (fd);
}

t_bmp	read_bmp(char *file)
{
	struct s_BMPFileHeader	header;
	struct s_BMPInfoHeader	infoheader;
	int						fd;
	t_bmp					image;
	int						skip;

	fd = open_file(file);
	checked_read(fd, &header, sizeof(header));
	if (header.file_type != 0x4D42)
		error("no bmp!");
	checked_read(fd, &infoheader, sizeof(infoheader));
	init_bmp_image(&image, infoheader);
	skip = header.offset_data - sizeof(header) - sizeof(infoheader);
	if (skip < 0)
		error("file corrupted!");
	while (skip--)
		checked_read(fd, &header, 1);
	image.data = ft_malloc_or_exit(image.bytes_per_row * image.height * sizeof(char));
	checked_read(fd, image.data, \
		image.bytes_per_row * image.height * sizeof(char));
	bgr_to_rgb(image.data, image.bytes_per_row * image.height * sizeof(char), \
		image.bytes_per_pixel);
	return (image);
}
