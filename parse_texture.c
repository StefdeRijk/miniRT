#include "miniRT.h"

void	parse_texture(t_bmp *texture, t_parse_line *line)
{
	char	filename[MAX_TEXTURE_FILE_SIZE];

	skip_zero_or_more_char(line, ' ');
	parse_string(line, filename, MAX_TEXTURE_FILE_SIZE);
	if (filename[0])
		*texture = read_bmp(filename);
	else
		texture->data = NULL;
}
