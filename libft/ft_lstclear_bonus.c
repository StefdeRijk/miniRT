/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:37:45 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:37:45 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (!*lst)
		return ;
	if (!(*lst)->next)
	{
		ft_lstdelone(*lst, del);
		return ;
	}
	ft_lstclear(&((*lst)->next), del);
	ft_lstdelone(*lst, del);
	*lst = 0;
}
