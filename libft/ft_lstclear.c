/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:16:03 by jyelena           #+#    #+#             */
/*   Updated: 2020/11/09 17:57:51 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *current;
	t_list *tempor;

	current = *lst;
	while (current)
	{
		tempor = current->next;
		ft_lstdelone(current, del);
		current = tempor;
	}
	*lst = NULL;
}
