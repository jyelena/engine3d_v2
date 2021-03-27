/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 22:51:48 by jyelena           #+#    #+#             */
/*   Updated: 2020/11/07 22:51:55 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char *string;

	string = (char *)malloc(sizeof(char) * 2);
	if (string == NULL)
		return (NULL);
	if (n == MIN_INT)
		return (ft_strcpy(string, C_MIN_INT));
	if (n < 0)
	{
		string[0] = '-';
		string[1] = '\0';
		string = ft_strjoin(string, ft_itoa(-n));
	}
	else if (n >= 10)
		string = ft_strjoin(ft_itoa(n / 10), ft_itoa(n % 10));
	else if (n < 10 && n >= 0)
	{
		string[0] = n + '0';
		string[1] = '\0';
	}
	return (string);
}
