#include "libft.h"

#define NAN_OR_INF 0x7ff
#define EXP_BIAS 1023

static double	ft_only_sign(t_modf_union u)
{
	u.l &= 1UL << 63;
	return (u.f);
}

static int	get_exponent(t_modf_union u)
{
	return (((u.l << 1) >> 53) - EXP_BIAS);
}

double	ft_modf(double a, double *intpart)
{
	int				exponent;
	t_modf_union	u;

	u.f = a;
	exponent = get_exponent(u);
	if (exponent >= 52)
	{
		*intpart = a;
		if (exponent == NAN_OR_INF)
			return (a);
		return (ft_only_sign(u));
	}
	if (exponent < 0)
	{
		*intpart = -1 * (u.l & 1UL << 63);
		return (a);
	}
	if ((u.l & -1UL >> 12 >> exponent) == 0)
	{
		*intpart = a;
		return (ft_only_sign(u));
	}
	u.l &= -1UL << (52 - exponent);
	*intpart = u.f;
	return (a - u.f);
}
