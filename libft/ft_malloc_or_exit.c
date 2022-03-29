#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

void	*ft_malloc_or_exit(size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
	{
		ft_putstr_fd("malloc failed\n", STDERR_FILENO);
		exit(1);
	}
	return (new);
}
