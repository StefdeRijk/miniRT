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

void	error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	checked_read(int fd, void *buffer, size_t size)
{
	if (read(fd, buffer, size) != size)
		error("read error");
}

void	bgr_to_rgb(unsigned char *image, uint32_t size)
{
	int				i;
	unsigned char	tmp;

	i = 0;
	while (i < size)
	{
		tmp = image[i];
		image[i] = image[i + 2];
		image[i + 2] = tmp;
		i += 3;
	}
}

unsigned char	*read_bmp(char *file)
{
	struct s_BMPFileHeader	header;
	struct s_BMPInfoHeader	infoheader;
	int						fd;
	unsigned char			*image;
	int						skip;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error();
	checked_read(fd, &header, sizeof(header));
	if (header.file_type != 0x4D42)
		error("no bmp!");
	checked_read(fd, &infoheader, sizeof(infoheader));
	skip = header.offset_data - sizeof(header) - sizeof(infoheader);
	if (skip < 0)
		error("file corrupted!");
	while (skip--)
		checked_read(fd, &header, 1);
	image = malloc(infoheader.size);
	if (!image)
		error("malloc failed");
	checked_read(fd, image, infoheader.size);
	bgr_to_rgb(image, infoheader.size);
	return (image);
}

int	main(void)
{
	read_bmp("seamless-normal-map.bmp");
}
