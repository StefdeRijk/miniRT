/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/06 11:25:30 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/06 11:25:30 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
