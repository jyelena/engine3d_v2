/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_strafe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 20:11:07 by jyelena           #+#    #+#             */
/*   Updated: 2021/04/30 22:38:24 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	strafe_right(t_game *game, double speed)
{
	if (PMAP[(int)(game->plr.pos_y)]
	[(int)(game->plr.pos_x - game->plr.dir_y * speed)] == '0')
		game->plr.pos_x -= game->plr.dir_y * speed;
	if (PMAP[(int)(game->plr.pos_y + game->plr.dir_x
	* speed)][(int)(game->plr.pos_x)] == '0')
		game->plr.pos_y += game->plr.dir_x * speed;
}

void	strafe_left(t_game *game, double speed)
{
	if (PMAP[(int)(game->plr.pos_y)]
	[(int)(game->plr.pos_x + game->plr.dir_y * speed)] == '0')
		game->plr.pos_x += game->plr.dir_y * speed;
	if (PMAP[(int)(game->plr.pos_y - game->plr.dir_x
	* speed)][(int)(game->plr.pos_x)] == '0')
		game->plr.pos_y -= game->plr.dir_x * speed;
}
