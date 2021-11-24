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
