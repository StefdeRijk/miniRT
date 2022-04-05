/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:37:48 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:37:48 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void *p, size_t size, size_t old_size)
{
	void	*new;

	new = malloc(size);
	if (new)
		ft_memcpy(new, p, old_size);
	free(p);
	return (new);
}
