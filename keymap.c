/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:30:20 by jyelena           #+#    #+#             */
/*   Updated: 2021/04/28 20:14:36 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int key, t_game *game)
{
	if (key == 13)
		game->mov.up = 1;
	if (key == 1)
		game->mov.down = 1;
	if (key == 124)
		game->mov.turn_right = 1;
	if (key == 123)
		game->mov.turn_left = 1;
	if (key == 0)
		game->mov.strafe_right = 1;
	if (key == 2)
		game->mov.strafe_left = 1;
	if (key == 53)
		exit(0);
	return (0);
}

int		key_release(int key, t_game *game)
{
	if (key == 13)
		game->mov.up = 0;
	if (key == 1)
		game->mov.down = 0;
	if (key == 124)
		game->mov.turn_right = 0;
	if (key == 123)
		game->mov.turn_left = 0;
	if (key == 0)
		game->mov.strafe_right = 0;
	if (key == 2)
		game->mov.strafe_left = 0;
	return (0);
}
