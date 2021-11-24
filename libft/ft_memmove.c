#include<stddef.h>
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!src && !dst)
		return (0);
	if (src > dst)
	{
		i = 0;
		while (i < n)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			((char *)dst)[i - 1] = ((char *)src)[i - 1];
			i--;
		}
	}
	return (dst);
}
