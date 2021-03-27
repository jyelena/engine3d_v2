/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 09:15:45 by jyelena           #+#    #+#             */
/*   Updated: 2020/11/09 17:45:48 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isinset(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	if (s != NULL)
	{
		end = ft_strlen(s);
		while (s[start] != '\0' && ft_isinset(s[start], set))
			start++;
		if (s[start] == '\0')
			return (ft_strdup(""));
		while (ft_isinset(s[end - 1], set))
			end--;
		if (ft_substr(s, start, end - start))
			return (ft_substr(s, start, end - start));
		return (0);
	}
	return (NULL);
}
