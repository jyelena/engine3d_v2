/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:35:10 by jyelena           #+#    #+#             */
/*   Updated: 2020/11/09 18:00:20 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newhead;

	if (!lst)
		return (NULL);
	newhead = ft_lstnew(f(lst->content));
	if (newhead == NULL)
		return (NULL);
	newlst = newhead;
	while (lst->next)
	{
		lst = lst->next;
		newlst->next = ft_lstnew(f(lst->content));
		if (newlst->next == NULL)
		{
			ft_lstclear(&newhead, del);
			return (NULL);
		}
		newlst = newlst->next;
	}
	newlst->next = NULL;
	return (newhead);
}
