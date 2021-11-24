#include<stdlib.h>
#include<stddef.h>

enum e_error {
	MY_SUCCESS,
	MY_ERROR
};

int	count_words(char const *s, char c)
{
	while (*s && *s == c)
		s++;
	if (!(*s))
		return (0);
	while (*s && *s != c)
		s++;
	return (1 + count_words(s, c));
}

int	place_words(char **res, char const *s, char c, int words)
{
	size_t	i;

	while (*s && *s == c)
		s++;
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!i)
		res[words] = 0;
	else
		res[words] = malloc((i + 1) * sizeof(char));
	if (!res[words] || !i)
		return (words);
	i = 0;
	while (*s && *s != c)
	{
		res[words][i] = *s;
		i++;
		s++;
	}
	res[words][i] = 0;
	return (place_words(res, s, c, words + 1));
}

void	cleanup(char **res, int words)
{
	while (words)
	{
		free(res[words]);
		words--;
	}
	free(res);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**res;
	int		words_placed;

	i = 0;
	i = count_words(s, c);
	res = malloc((i + 1) * sizeof(char *));
	if (!res)
		return (0);
	words_placed = place_words(res, s, c, 0);
	if (words_placed < i)
	{
		cleanup(res, words_placed);
	}
	return (res);
}
