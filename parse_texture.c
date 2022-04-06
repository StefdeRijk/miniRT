/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_texture.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/06 11:25:33 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/06 11:25:33 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
