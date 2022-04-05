/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:37:47 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:37:47 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memdup(const void *m, size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		return (NULL);
	ft_memcpy(res, m, size);
	return (res);
}
