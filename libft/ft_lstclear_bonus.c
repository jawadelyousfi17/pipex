/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:18:50 by jel-yous          #+#    #+#             */
/*   Updated: 2024/11/13 12:48:08 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*holder;

	if (!lst || !del)
		return ;
	holder = *lst;
	tmp = *lst;
	while (tmp)
	{
		holder = tmp;
		(*del)(holder->content);
		tmp = tmp->next;
		free(holder);
	}
	*lst = NULL;
}
