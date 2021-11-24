#include "libft.h"
#include "stdlib.h"

void	ft_lstremove(t_list **lst, t_list *rem, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!*lst)
		return ;
	if (rem == *lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
		return ;
	}
	current = *lst;
	next = current->next;
	while (next && next != rem)
	{
		current = next;
		next = current->next;
	}
	if (next)
	{
		current->next = next->next;
		ft_lstdelone(next, del);
	}
}
