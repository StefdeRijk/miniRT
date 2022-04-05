/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:37:50 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:37:50 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*found;

	found = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			found = ((char *)s + i);
		i++;
	}
	if (!c)
		found = ((char *)s + i);
	return (found);
}
