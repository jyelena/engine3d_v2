/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:57:16 by jyelena           #+#    #+#             */
/*   Updated: 2020/11/01 11:35:07 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *str;
	unsigned char symbol;

	symbol = (unsigned char)c;
	str = (unsigned char *)s;
	while (n > 0)
	{
		if (*str == symbol)
			return (str);
		str++;
		n--;
	}
	return (NULL);
}
