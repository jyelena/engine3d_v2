/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_router.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:13:27 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/04/26 22:30:27 by dmikhaylov       ###   ########.fr       */
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

int		prs_map_rout(t_game *game, char **str, int *flg, t_list **tmp)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(*str);
	if (len == 0)
	{
		free(*str);
		*str = NULL;
		return (-2);
	}
	ft_lstadd_back(tmp, ft_lstnew(*str));
	while (len > 0 && (*str)[i])
	{
		if ((*str)[i] != 32 && !chk_in_set((*str)[i], flg))
			return (-2);
		if ((*str)[i] == '2')
			game->scount++;
		i++;
	}
	game->map.d++;
	if (*flg > 0)
		if (len > game->map.w)
			game->map.w = len;
	return (1);
}
