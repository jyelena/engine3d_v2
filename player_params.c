/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 21:57:48 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/04/26 22:28:49 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_plane(t_game *game)
{
	if (game->plr.dir == 'N')
	{
		game->plr.plane_x = 0.66;
		game->plr.plane_y = 0.0;
	}
	else if (game->plr.dir == 'S')
	{
		game->plr.plane_x = -0.66;
		game->plr.plane_y = 0.0;
	}
	else if (game->plr.dir == 'E')
	{
		game->plr.plane_x = 0.0;
		game->plr.plane_y = 0.66;
	}
	else if (game->plr.dir == 'W')
	{
		game->plr.plane_x = 0.0;
		game->plr.plane_y = -0.66;
	}
}

void	player_dir(t_game *game)
{
	if (game->plr.dir == 'N')
	{
		game->plr.dir_x = 0.0;
		game->plr.dir_y = -1.0;
	}
	else if (game->plr.dir == 'S')
	{
		game->plr.dir_x = 0.0;
		game->plr.dir_y = 1.0;
	}
	else if (game->plr.dir == 'E')
	{
		game->plr.dir_x = 1.0;
		game->plr.dir_y = 0.0;
	}
	else if (game->plr.dir == 'W')
	{
		game->plr.dir_x = -1.0;
		game->plr.dir_y = 0.0;
	}
	player_plane(game);
}

void 	player_position(int x, int y, t_game *game)
{
	game->plr.pos_x = x + 0.5;
	game->plr.pos_y = y + 0.5;
	game->plr.dir = game->map.mp[y][x];
	player_dir(game);
}
