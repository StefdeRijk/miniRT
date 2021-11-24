#include "libft.h"
int	ft_atoi_base(const char *str, int base, char ten)
{
	int		sign;
	long	res;

	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = 0;
	while ((*str >= '0' && *str <= ft_min('0' + base - 1, '9'))
		|| (*str >= ten && *str <= ten - 11 + base))
	{
		res *= base;
		if (*str >= '0' && *str <= '9')
			res += (*str - '0');
		else
			res += (*str - ten + 10);
		str++;
	}
	res *= sign;
	return (res);
}
