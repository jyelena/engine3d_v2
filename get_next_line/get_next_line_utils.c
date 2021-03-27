/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 18:43:01 by jyelena           #+#    #+#             */
/*   Updated: 2021/01/27 10:30:57 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

int		ft_substr_len(char const *s, char c)
{
	char const *h;

	if (!s)
		return (0);
	if (!c)
		c = '\0';
	h = s;
	while (*s && *s != c)
		s++;
	return (s - h);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	int		i;
	char	*head;

	if (!s1 || !s2)
		return (NULL);
	head = s1;
	result = malloc(ft_substr_len(s1, 0) + ft_substr_len(s2, 0) + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		result[i] = *s1++;
		i++;
	}
	while (*s2)
	{
		result[i] = *s2++;
		i++;
	}
	result[i] = '\0';
	free(head);
	return (result);
}
