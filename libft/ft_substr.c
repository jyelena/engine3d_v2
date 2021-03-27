/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:52:44 by jyelena           #+#    #+#             */
/*   Updated: 2020/11/09 17:46:49 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		if (!(result = (char *)malloc(sizeof(char))))
			return (NULL);
		result[0] = '\0';
		return (result);
	}
	else if ((unsigned int)ft_strlen(s) - start < (unsigned int)len) {
		len = (unsigned int)ft_strlen(s) - start;
	}
	if (!(result = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (len)
	{
		result[i++] = s[start++];
		len--;
	}
	result[i] = '\0';
	return (result);
}
