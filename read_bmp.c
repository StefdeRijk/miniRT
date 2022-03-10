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

int	main(void)
{
	struct s_BMPFileHeader	header;
	struct s_BMPInfoHeader	infoheader;
	char					dump[1000];
	int						fd;
	unsigned char			*image;
	int						i;
	unsigned char			tmp;

	fd = open("seamless-normal-map.bmp", O_RDONLY);
	if (fd == -1)
	{
		printf("error!\n");
		exit(1);
	}
	read(fd, &header, sizeof(header));
	if (header.file_type != 0x4D42)
	{
		printf("no bmp!\n");
		exit(1);
	}
	printf("it works!\n");
	read(fd, &infoheader, sizeof(infoheader));
	printf("width: %d\n", infoheader.width);
	if (header.offset_data - sizeof(header) - sizeof(infoheader) < 0)
	{
		printf("file corrupted!\n");
		exit(1);
	}
	printf("skipped bytes: %lu\n", (header.offset_data - sizeof(header) - sizeof(infoheader)));
	if (header.offset_data - sizeof(header) - sizeof(infoheader) > 0)
		read(fd, dump, header.offset_data - sizeof(header) - sizeof(infoheader));
	image = malloc(infoheader.size);
	if (!image)
		exit(1);
	read(fd, image, infoheader.size);
	printf("%X %X %X\n", image[0], image[1], image[2]);
	i = 0;
	while (i < infoheader.size)
	{
		tmp = image[i];
		image[i] = image[i + 2];
		image[i + 2] = tmp;
		i += 3;
	}
	printf("%X %X %X\n", image[0], image[1], image[2]);
}
