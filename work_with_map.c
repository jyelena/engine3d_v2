/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 02:08:55 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/03/28 01:21:01 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		chk_on_top(int y, int x, t_game *game)
{
	if (!(game->map.mp[y - 1][x] == 32 || game->map.mp[y - 1][x] == 49
	|| game->map.mp[y - 1][x] == 0))
		return (-2);
	if (x > 0 && !(game->map.mp[y - 1][x - 1] == 32
	|| game->map.mp[y - 1][x - 1] == 49 || game->map.mp[y - 1][x - 1] == 0))
		return (-2);
	if (x < game->map.w - 1 && !(game->map.mp[y - 1][x + 1] == 32
	|| game->map.mp[y - 1][x + 1] == 49 || game->map.mp[y - 1][x + 1] == 0))
		return (-2);
	return (1);
}

int		chk_on_bottom(int y, int x, t_game *game)
{
	if (!(game->map.mp[y + 1][x] == 32 || game->map.mp[y + 1][x] == 49
	|| game->map.mp[y + 1][x] == 0))
		return (-2);
	if (x > 0 && !(game->map.mp[y + 1][x - 1] == 32
	|| game->map.mp[y + 1][x - 1] == 49 || game->map.mp[y + 1][x - 1] == 0))
		return (-2);
	if (x < game->map.w - 1 && !(game->map.mp[y + 1][x + 1] == 32
	|| game->map.mp[y + 1][x + 1] == 49 || game->map.mp[y + 1][x + 1] == 0))
		return (-2);
	return (1);
}

int		chk_round(int y, int x, t_game *game)
{
	if ((y > 0 && chk_on_top(y, x, game) < 0)
	|| (y < game->map.d - 1 && chk_on_bottom(y, x, game) < 0))
		return (-2);
	if (x > 0 && !(game->map.mp[y][x - 1] == 32 || game->map.mp[y][x - 1] == 49
	|| game->map.mp[y][x - 1] == 0))
		return (-2);
	if (x < game->map.w - 1 && !(game->map.mp[y][x + 1] == 32
	|| game->map.mp[y][x + 1] == 49 || game->map.mp[y][x + 1] == 0))
		return (-2);
	return (1);
}

int		valid_map(t_game *game)
{
	int y;
	int x;

	y = 0;
	while (y < game->map.d)
	{
		x = 0;
		while (x < game->map.w)
		{
			if (game->map.mp[y][x] == ' ')
			{
				if (chk_round(y, x, game) < 0)
					return (red_flag(-2, game));
			}
			if (game->map.mp[y][x] == 'N' || game->map.mp[y][x] == 'S'
			|| game->map.mp[y][x] == 'W' || game->map.mp[y][x] == 'E')
			{
				player_position(x, y, game);
			}
			x++;
		}
		y++;
	}
	fill_sprites_struct(game);
	return (1);
}

int		make_map(t_game *game, t_list **tmp_map)
{
	int		d;
	t_list	*tmp;

	tmp = *tmp_map;
	d = 0;
	while ((*tmp_map) && d < game->map.d - 1)
	{
		game->map.mp[d] = (char *)ft_memset((void *)game->map.mp[d], 32,
		game->map.w);
		if (d > 0 && d < game->map.d - 1)
		{
			line_cpy(tmp->content, &game->map.mp[d], game);
			tmp = tmp->next;
		}
		d++;
	}
	game->map.mp[d] = (char *)ft_memset((void *)game->map.mp[d], 32,
	game->map.w);
	free_list(tmp_map);
	return (1);
}
