/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_router.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:13:27 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/05/01 04:37:14 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	line_cpy(char *source, char **dest, t_game *game)
{
	int	i;

	i = 0;
	while (source && *source && i <= game->map.w - 1)
	{
		if (i > 0)
		{
			(*dest)[i] = *source;
			source++;
		}
		i++;
	}
}

void	chk_bigger_len(int *flg, int len, t_game *game)
{
	if (*flg > 0)
		if (len > game->map.w)
			game->map.w = len;
}

int		chk_len(int len, int *flg)
{
	if (len == 0 && *flg)
		return (1);
	return (0);
}

int		prs_map_rout(t_game *game, char **str, int *flg, t_list **tmp)
{
	int		len;
	int		i;

	len = ft_strlen(*str);
	i = 0;
	if (chk_len(len, flg))
	{
		free(*str);
		*str = NULL;
		return (-2);
	}
	if (len == 0)
		return (1);
	while (len > 0 && (*str)[i])
	{
		if (!chk_in_set((*str)[i], flg))
			return (-2);
		if ((*str)[i] == '2')
			game->scount++;
		i++;
	}
	ft_lstadd_back(tmp, ft_lstnew(*str));
	game->map.d++;
	chk_bigger_len(flg, len, game);
	return (1);
}
