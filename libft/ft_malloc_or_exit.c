/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_malloc_or_exit.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:37:46 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:37:46 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

void	*ft_malloc_or_exit(size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
	{
		ft_putstr_fd("malloc failed\n", STDERR_FILENO);
		exit(1);
	}
	return (new);
}
