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
