#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	if (!(*lst)->next)
	{
		(*lst)->next = new;
		return ;
	}
	return (ft_lstadd_back(&((*lst)->next), new));
}
