/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 22:05:01 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/04/26 22:25:53 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 	swap_sprites(t_game *game, int i)
{
	t_spr	spr_tmp;

	spr_tmp = (game->spr)[i];
	(game->spr)[i] = (game->spr)[i + 1];
	(game->spr)[i + 1] = spr_tmp;
}

void 	sort_sprites(t_game *game)
{
	int		i;
	int 	flg;
	i = 0;
	flg = 1;
	while (flg)
	{
		flg = 0;
		while (i < game->scount - 1)
		{
			if ((game->spr)[i].dist < (game->spr)[i + 1].dist)
			{
				swap_sprites(game, i);
				flg = 1;
			}
			i++;
		}
	}
}

void 	calc_sprite_dist(t_game *game)
{
	int	i;

	i = 0;
	while(i < game->scount)
	{
		(game->spr)[i].dist = ((game->plr.pos_x - (game->spr)[i].x)
		* (game->plr.pos_x - (game->spr)[i].x) + (game->plr.pos_y
												  - (game->spr)[i].y) *
												  (game->plr.pos_y - (game->spr)
												  [i].y));
		i++;
	}
}

void	fill_sprites_struct(t_game *game)
{
	int		x;
	int		y;
	int 	i;

	i = 0;
	if (!(game->spr = (t_spr *)malloc(sizeof(t_spr) * game->scount)))
		return ;
	y = 0;
	while (game->map.mp[y])
	{
		x = 0;
		while (game->map.mp[y][x])
		{
			if (game->map.mp[y][x] == '2')
			{
				(game->spr)[i].x = x + 0.5;
				(game->spr)[i].y = y + 0.5;
				i++;
			}
			x++;
		}
		y++;
	}
	calc_sprite_dist(game);
	sort_sprites(game);
}