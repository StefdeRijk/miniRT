#include "stdlib.h"
#include "libft/libft.h"
#include "vec.h"

void	vec_pop(t_vec *vec, int i)
{
	ft_memmove(((char *)vec->data) + i * vec->elem_size, ((char *)vec->data)
		+ (i + 1) * vec->elem_size, (vec->len - i - 1) * vec->elem_size);
	vec->len--;
}

void	vec_pop_n(t_vec *vec, int i, int n)
{
	ft_memmove(((char *)vec->data) + i * vec->elem_size, ((char *)vec->data)
		+ (i + n) * vec->elem_size, (vec->len - i - n) * vec->elem_size);
	vec->len -= n;
}

/*
void	vec_print(t_vec *vec)
{
	int	i;
	int	j;

	i = 0;
	while (i < vec->len)
	{
		j = vec->data[i];
		if (j == PA)
			ft_putstr_fd("pa", 1);
		else if (j == PB)
			ft_putstr_fd("pb", 1);
		else if (j == RA)
			ft_putstr_fd("ra", 1);
		else if (j == RB)
			ft_putstr_fd("rb", 1);
		else
		{
			ft_putstr_fd("Unknown symbol found", 1);
			ft_putnbr_fd(j, 1);
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}
*/

void	vec_init(t_vec *vec, int elem_size)
{
	vec->cap = 10;
	vec->len = 0;
	vec->elem_size = elem_size;
	vec->data = malloc(vec->elem_size * vec->cap);
}

void	vec_push_n(t_vec *vec, void *i, int n)
{
	size_t	new_cap;

	if (vec->len + n > vec->cap)
	{
		new_cap = vec->cap * 2 + n;
		vec->data = ft_realloc(vec->data, new_cap * vec->elem_size,
				vec->cap * vec->elem_size);
		vec->cap = new_cap;
	}
	ft_memcpy((char *)vec->data + vec->len, i, vec->elem_size * n);
	vec->len += n;
}

void	vec_push(t_vec *vec, void *i)
{
	size_t	new_cap;

	if (vec->len == vec->cap)
	{
		new_cap = vec->cap * 2 + 1;
		vec->data = ft_realloc(vec->data, new_cap * vec->elem_size,
				vec->cap * vec->elem_size);
		vec->cap = new_cap;
	}
	ft_memcpy((char *)vec->data + (vec->len * vec->elem_size), i, vec->elem_size);
	vec->len++;
}
