/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:30:57 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/03/27 23:36:47 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	file_init(t_fname *file)
{
	file->name = "./snapshot.bmp";
}

void	move_init(t_game *game)
{
	game->mov.up = 0;
	game->mov.down = 0;
	game->mov.turn_left = 0;
	game->mov.turn_right = 0;
	game->mov.strafe_left = 0;
	game->mov.strafe_right = 0;
	game->mov.exit = 0;
}

void	cub_init(t_game *game)
{
	game->ok = 1;
	game->scount = 0;
	game->map.w = 0;
	game->map.d = 0;
	game->chk.r = 0;
	game->chk.f = 0;
	game->chk.c = 0;
	game->chk.no = 0;
	game->chk.so = 0;
	game->chk.we = 0;
	game->chk.ea = 0;
	game->chk.sp = 0;
	game->resolution.x = -1;
	game->resolution.y = -1;
	game->colors.ceil_color.r = -1;
	game->colors.ceil_color.g = -1;
	game->colors.ceil_color.b = -1;
	game->colors.floor_color.r = -1;
	game->colors.floor_color.g = -1;
	game->colors.floor_color.b = -1;
	move_init(game);
}

void	wrt_err(char *text)
{
	while (*text)
		write(1, text++, 1);
	write(1, "\n", 1);
}
