/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:17:36 by jyelena           #+#    #+#             */
/*   Updated: 2020/11/09 17:39:53 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t k;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			k = 0;
			while (needle[k] && haystack[i + k] == needle[k] && i + k < len)
			{
				if (!needle[k + 1])
					return ((char *)&haystack[i]);
				k++;
			}
		}
		i++;
	}
	return (NULL);
}
