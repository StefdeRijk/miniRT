#include<stdlib.h>
#include<stddef.h>

char	*my_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	if (!c)
		return ((char *)(s + i));
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*res;

	while (*s1 && my_strchr(set, *s1))
		s1++;
	i = 0;
	len = 0;
	while (s1[i])
	{
		if (!my_strchr(set, s1[i]))
			len = i + 1;
		i++;
	}
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (i < len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = 0;
	return (res);
}
