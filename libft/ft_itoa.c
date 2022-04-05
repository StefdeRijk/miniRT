/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:37:07 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:37:07 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	place_num(char *res, long n, int div, int leading)
{
	long	num;

	if (div == 0)
	{
		*res = 0;
		return ;
	}
	num = n / div;
	if (num)
		leading = 0;
	if (!leading)
	{
		*res = num + '0';
		res++;
	}
	place_num(res, n % div, div / 10, leading);
}

char	*my_alloc(long n)
{
	int	size;

	if (!n)
		return (malloc((2) * sizeof(char)));
	size = 0;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		size++;
	}
	return (malloc((size + 1) * sizeof(char)));
}

char	*ft_itoa(int n)
{
	char	*res;
	char	*res_copy;
	long	nl;

	nl = n;
	res = my_alloc(nl);
	res_copy = res;
	if (!res)
		return (0);
	if (n == 0)
	{
		res[0] = '0';
		res++;
	}
	if (n < 0)
	{
		res[0] = '-';
		nl *= -1;
		res++;
	}
	place_num(res, nl, 1000000000, 1);
	return (res_copy);
}
