/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:37:07 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:37:07 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
