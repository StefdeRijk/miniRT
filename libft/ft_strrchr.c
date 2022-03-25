#include<stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*found;

	found = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			found = ((char *)s + i);
		i++;
	}
	if (!c)
		found = ((char *)s + i);
	return (found);
}
