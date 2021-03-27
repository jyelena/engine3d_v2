/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:57:56 by jyelena           #+#    #+#             */
/*   Updated: 2020/11/01 11:43:01 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*destination;
	unsigned const char	*source;

	destination = dest;
	source = src;
	if (destination == 0 && source == 0)
		return (NULL);
	if (destination < source)
	{
		while (n--)
			*destination++ = *source++;
	}
	else
	{
		destination += n - 1;
		source += n - 1;
		while (n--)
			*destination-- = *source--;
	}
	return ((void *)dest);
}
