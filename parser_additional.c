/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_additional.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:15:21 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/03/29 01:05:31 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		chk_in_set(char c, int *flg)
{
	char	*set;

	set = "012NWES";
	while (*set)
	{
		if (c == *set)
		{
			if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
			{
				if (*flg < 10)
					*flg += 10;
				else
					return (0);
			}
			if (*flg == 0)
				*flg += 1;
			return (1);
		}
		set++;
	}
	return (0);
}

int		chk_map_conf(t_game *game)
{
	return (game->chk.r + game->chk.f + game->chk.c + game->chk.no
	+ game->chk.so + game->chk.we + game->chk.ea + game->chk.sp);
}

int		fill_num(char **str, int size)
{
	int		i;
	int		res;
	char	num[10];
	int		fl;

	fl = 0;
	ft_bzero(num, size);
	i = 0;
	while (*(*str) >= '0' && *(*str) <= '9' && i < size)
	{
		if (*(*str) != 48 || !(*(*str + 1)))
			fl = 1;
		if (fl > 0)
		{
			num[i] = *(*str);
			i++;
		}
		(*str)++;
	}
	res = ft_atoi(num);
	if ((size == 10 && res < 1) || (size == 3 && (res < 0 || res > 255)))
		return (-1);
	return (res);
}

int		trim_space_end(char **str)
{
	int		i;
	int		max_idx;

	max_idx = (int)ft_strlen((*str)) - 1;
	i = max_idx;
	while ((*str)[i] == 32)
	{
		(*str)[i] = '\0';
		i--;
	}
	return (max_idx);
}

int		trim_space(char **str)
{
	int		i;
	int		k;
	int		len;

	i = 0;
	k = 0;
	len = ft_strlen(*str);
	while (i < len)
	{
		if (k != i)
			(*str)[k] = (*str)[i];
		if ((*str)[i] == 32)
		{
			while ((*str)[i + 1] == 32)
				i++;
		}
		k++;
		i++;
	}
	(*str)[k] = '\0';
	return (len);
}
