/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:37:49 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:37:49 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*res;

	i = 0;
	while (s1[i])
		i++;
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = 0;
	return (res);
}
