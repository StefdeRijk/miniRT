#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

int	main() {
	struct s_BMPFileHeader header;
	struct s_BMPInfoHeader infoheader;
	FILE* file = fopen("seamless-normal-map.bmp", "rb");
	unsigned char *image;
	int i;
	unsigned char tmp;
	if (!file)
	{
		printf("error!\n");
		exit(1);
	}
	fread(&header, sizeof(header), 1, file);
	if (header.file_type != 0x4D42) {
		printf("no bmp!\n");
		exit(1);
	}
	printf("it works!\n");
	fread(&infoheader, sizeof(infoheader), 1, file);
	printf("width: %d\n", infoheader.width);
	fseek(file, header.offset_data, SEEK_SET);
	image = malloc(infoheader.size);
	if (!image)
		exit(1);
	fread(image, infoheader.size, 1, file);
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
