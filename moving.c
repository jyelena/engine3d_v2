/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:31:25 by jyelena           #+#    #+#             */
/*   Updated: 2021/04/30 06:32:07 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_game *game, double move_speed)
{
	if (PMAP[(int)(game->plr.pos_y)]
	[(int)(game->plr.pos_x + game->plr.dir_x * move_speed)] == '0')
		game->plr.pos_x += game->plr.dir_x * move_speed;
	if (PMAP[(int)(game->plr.pos_y + game->plr.dir_y * move_speed)]
	[(int)(game->plr.pos_x)] == '0')
		game->plr.pos_y += game->plr.dir_y * move_speed;
}

void	move_down(t_game *game, double move_speed)
{
	if (PMAP[(int)(game->plr.pos_y)]
	[(int)(game->plr.pos_x - game->plr.dir_x * move_speed)] == '0')
		game->plr.pos_x -= game->plr.dir_x * move_speed;
	if (PMAP[(int)(game->plr.pos_y - game->plr.dir_y * move_speed)]
	[(int)(game->plr.pos_x)] == '0')
		game->plr.pos_y -= game->plr.dir_y * move_speed;
}

void	turn_right(t_game *game, double move_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = game->plr.dir_x;
	game->plr.dir_x = game->plr.dir_x * cos(move_speed)
	- game->plr.dir_y * sin(move_speed);
	game->plr.dir_y = old_dir_x * sin(move_speed)
	+ game->plr.dir_y * cos(move_speed);
	old_plane_x = game->plr.plane_x;
	game->plr.plane_x = game->plr.plane_x * cos(move_speed)
	- game->plr.plane_y * sin(move_speed);
	game->plr.plane_y = old_plane_x * sin(move_speed)
	+ game->plr.plane_y * cos(move_speed);
}

void	turn_left(t_game *game, double move_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = game->plr.dir_x;
	game->plr.dir_x = game->plr.dir_x * cos(-move_speed)
	- game->plr.dir_y * sin(-move_speed);
	game->plr.dir_y = old_dir_x * sin(-move_speed)
	+ game->plr.dir_y * cos(-move_speed);
	old_plane_x = game->plr.plane_x;
	game->plr.plane_x = game->plr.plane_x * cos(-move_speed)
	- game->plr.plane_y * sin(-move_speed);
	game->plr.plane_y = old_plane_x * sin(-move_speed)
	+ game->plr.plane_y * cos(-move_speed);
}

int		moving(t_game *game)
{
	double	move_speed;

	move_speed = MULTSTRAFE / 2.01;
	if (game->mov.up)
		move_up(game, move_speed);
	if (game->mov.down)
		move_down(game, move_speed);
	if (game->mov.turn_right)
		turn_right(game, move_speed);
	if (game->mov.turn_left)
		turn_left(game, move_speed);
	if (game->mov.strafe_right)
		strafe_left(game, move_speed);
	if (game->mov.strafe_left)
		strafe_right(game, move_speed);
	draw_magic(game, 0, -1);
	return (0);
}
