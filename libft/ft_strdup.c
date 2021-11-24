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
