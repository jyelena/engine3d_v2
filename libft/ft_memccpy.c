/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:57:00 by jyelena           #+#    #+#             */
/*   Updated: 2020/11/01 11:33:07 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t len)
{
	unsigned char *destination;
	unsigned char *source;
	unsigned char symbol;

	symbol = (unsigned char)c;
	destination = (unsigned char *)dest;
	source = (unsigned char *)src;
	while (len-- > 0)
	{
		*destination = *source;
		if (*destination == symbol)
			return (++destination);
		destination++;
		source++;
	}
	return (0);
}
