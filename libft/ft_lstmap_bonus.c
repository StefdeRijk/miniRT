/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:37:46 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:37:46 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (del)(void *))
{
	t_list	*new;

	if (!lst)
		return (0);
	if (!(lst->next))
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
			return (0);
		ft_lstdelone(lst, del);
		new->next = 0;
		return (new);
	}
	new = ft_lstnew(f(lst->content));
	if (!new)
	{
		return (0);
	}
	new->next = ft_lstmap(lst->next, f, del);
	if (!new->next)
	{
		ft_lstdelone(new, del);
		return (0);
	}
	return (new);
}
