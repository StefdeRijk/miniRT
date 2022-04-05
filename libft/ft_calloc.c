/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:37:06 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:37:06 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*res;

	i = 0;
	res = malloc(count * size);
	if (!res)
		return (0);
	while (i < size * count)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}
