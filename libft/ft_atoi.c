/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 09:19:13 by jyelena           #+#    #+#             */
/*   Updated: 2020/11/04 09:19:16 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long num;
	long sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || *str == '\r' || *str == '\n' || *str == '\f' || *str
	== '\t' || *str == '\v')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		if ((num * sign) > MAX_INT)
			return (-1);
		if ((num * sign) < MIN_INT)
			return (0);
		str++;
	}
	return ((int)(num * sign));
}
