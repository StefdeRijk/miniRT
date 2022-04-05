/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc_or_exit.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:37:48 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:37:48 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

void	*ft_realloc_or_exit(void *p, size_t size, size_t old_size)
{
	void	*new;

	new = ft_realloc(p, size, old_size);
	if (!new)
	{
		ft_putstr_fd("realloc failed\n", STDERR_FILENO);
		exit(1);
	}
	return (new);
}
