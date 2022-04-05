/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putmem_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:37:48 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:37:48 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"
#include "unistd.h"

void	ft_putmem_fd(void *c, size_t n, int fd)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		write(fd, (char *)(c + i), 1);
		i++;
	}
}
