/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_bmp.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/06 11:25:34 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/06 11:25:34 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	checked_read(int fd, void *buffer, long size, char *file)
{
	if (read(fd, buffer, size) != size)
	{
		printf("%s\n", file);
		error("read error");
	}
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
		error("could not open file");
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
	checked_read(fd, &header, sizeof(header), file);
	check_magic(header.file_type, file);
	checked_read(fd, &infoheader, sizeof(infoheader), file);
	init_bmp_image(&image, infoheader);
	skip = header.offset_data - sizeof(header) - sizeof(infoheader);
	if (skip < 0)
		error("file corrupted!");
	while (skip--)
		checked_read(fd, &header, 1, file);
	image.data = ft_malloc_or_exit(image.bytes_per_row * image.height * \
		sizeof(char));
	checked_read(fd, image.data, \
		image.bytes_per_row * image.height * sizeof(char), file);
	bgr_to_rgb(image.data, image.bytes_per_row * image.height * sizeof(char), \
		image.bytes_per_pixel);
	close(fd);
	return (image);
}
