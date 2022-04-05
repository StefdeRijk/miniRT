/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstremove_back.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:37:46 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:37:46 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstremove_back(t_list **lst, void (*del)(void *))
{
	if (!*lst)
	{
		ft_putstr_fd("Nothing to remove!", 2);
		exit(1);
		return ;
	}
	if (!(*lst)->next)
	{
		ft_lstdelone(*lst, del);
		*lst = NULL;
		return ;
	}
	ft_lstremove_back(&((*lst)->next), del);
}
