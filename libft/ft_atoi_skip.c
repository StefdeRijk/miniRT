#include "libft.h"
int	ft_atoi_skip(char **str)
{
	int		sign;
	long	res;

	sign = 1;
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	res = 0;
	while (**str >= '0' && **str <= '9')
	{
		res *= 10;
		res += (**str - '0');
		(*str)++;
	}
	res *= sign;
	return (res);
}
