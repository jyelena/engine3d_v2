/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:51:15 by jyelena           #+#    #+#             */
/*   Updated: 2020/11/01 12:07:37 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	int				result;
	unsigned long	i;

	result = 0;
	i = 0;
	while (((s1[i] != '\0' || s2[i] != '\0') && result == 0) && i < n)
	{
		if (s1[i] == s2[i])
			result = 0;
		else if ((s1[i] > s2[i] || s2[i] == '\0')
				|| (s1[i] < s2[i] || s1[i] == '\0'))
			result = (unsigned char)s1[i] - s2[i];
		i++;
	}
	return (result);
}
