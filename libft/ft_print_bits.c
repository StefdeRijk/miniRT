#include "libft.h"

void	ft_print_bits(long a)
{
	unsigned long	i;

	i = 1UL << 63;
	while (i >= 1)
	{
		ft_putchar_fd('0' + !!(a & i), 1);
		i >>= 1UL;
	}
}
