/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstremove_n.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 16:37:46 by dnoom         #+#    #+#                 */
/*   Updated: 2022/04/05 16:37:46 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

void	ft_lstremove_n(t_list **lst, t_list *rem, void (*del)(void *), int n)
{
	int		i;
	t_list	*next;

	i = 0;
	while (i < n)
	{
		next = rem->next;
		ft_lstremove(lst, rem, del);
		rem = next;
		i++;
	}
}
