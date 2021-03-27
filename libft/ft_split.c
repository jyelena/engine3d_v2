/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 22:56:55 by jyelena           #+#    #+#             */
/*   Updated: 2020/11/07 22:56:56 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counter(const char *s, char c)
{
	int	cnt;
	int	inside;

	inside = 0;
	cnt = 0;
	while (*s != '\0')
	{
		if (inside == 1 && *s == c)
			inside = 0;
		if (inside == 0 && *s != c)
		{
			inside = 1;
			cnt++;
		}
		s++;
	}
	return (cnt);
}

static int	ft_substr_len(char const *s, char c)
{
	char const *h;

	h = s;
	while (*s != c && *s != '\0')
		s++;
	return (s - h);
}

char		**ft_split(char const *s, char c)
{
	char	**result;
	int		nb_word;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	nb_word = ft_counter((const char *)s, c);
	if (!(result = (char **)malloc(sizeof(*result) * (ft_counter(s, c) + 1))))
		return (NULL);
	while (nb_word--)
	{
		while (*s == c && *s != '\0')
			s++;
		if (!(result[i++] = ft_substr(s, 0, ft_substr_len(s, c))))
		{
			while (--i >= 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		s = s + ft_substr_len(s, c);
	}
	result[i] = NULL;
	return (result);
}
