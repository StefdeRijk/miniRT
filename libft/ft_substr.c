/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:37:50 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:37:50 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<stddef.h>
#include<stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (s[i] && i < start)
		i++;
	s += i;
	i = 0;
	while (s[i] && i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = 0;
	return (res);
}
