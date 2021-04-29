/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_strafe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 20:11:07 by jyelena           #+#    #+#             */
/*   Updated: 2021/04/28 20:11:13 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	strafe_left(t_game *game, double speed)
{
	if (game->map.mp[(int)(game->plr.pos_y)]
	[(int)(game->plr.pos_x - game->plr.dir_y * (speed * MULTSTRAFE))] != '1'
	&& game->map.mp[(int)(game->plr.pos_y)]
	[(int)(game->plr.pos_x - game->plr.dir_y * (speed * MULTSTRAFE))] != '2')
		game->plr.pos_x += game->plr.dir_y * speed;
	if (game->map.mp[(int)(game->plr.pos_y + game->plr.dir_x
	* (speed * MULTSTRAFE))][(int)(game->plr.pos_x)] != '1'
	&& game->map.mp[(int)(game->plr.pos_y + game->plr.dir_x
	* (speed * MULTSTRAFE))][(int)(game->plr.pos_x)] != '2')
		game->plr.pos_y -= game->plr.dir_x * speed;
}

void	strafe_right(t_game *game, double speed)
{
	if (game->map.mp[(int)(game->plr.pos_y)]
	[(int)(game->plr.pos_x + game->plr.dir_y * (speed * MULTSTRAFE))] != '1'
	&& game->map.mp[(int)(game->plr.pos_y)]
	[(int)(game->plr.pos_x + game->plr.dir_y * (speed * MULTSTRAFE))] != '2')
		game->plr.pos_x -= game->plr.dir_y * speed;
	if (game->map.mp[(int)(game->plr.pos_y - game->plr.dir_x
	* (speed * MULTSTRAFE))][(int)(game->plr.pos_x)] != '1'
	&& game->map.mp[(int)(game->plr.pos_y - game->plr.dir_x
	* (speed * MULTSTRAFE))][(int)(game->plr.pos_x)] != '2')
		game->plr.pos_y += game->plr.dir_x * speed;
}
