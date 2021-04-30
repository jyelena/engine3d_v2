/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:29:57 by jyelena           #+#    #+#             */
/*   Updated: 2021/04/30 22:03:51 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_put_sprites(t_sprt *spr, t_game *game)
{
	while (spr->y < spr->drw_end_y)
	{
		spr->d = (spr->y) * 256 - H * 128 + spr->sprt_h * 128;
		spr->tex_y = ((spr->d * TEXHEIGH) / spr->sprt_h) / 256;
		spr->color = take_pixel(game->tex.sp, spr->tex_x, spr->tex_y);
		if ((int)(*(spr->color)) != 0x000000)
			my_mlx_pixel_put(game, spr->strp, spr->y, (int)(*(spr->color)));
		spr->y++;
	}
}

void	draw_spr_prepare(t_sprt *spr, t_game *game, int s)
{
	spr->sprt_x = (game->spr)[s].x - game->plr.pos_x + 0.5;
	spr->sprt_y = (game->spr)[s].y - game->plr.pos_y + 0.5;
	spr->inv_det = 1.0 / (game->plr.plane_x * game->plr.dir_y
	- game->plr.dir_x * game->plr.plane_y);
	spr->trform_x = spr->inv_det * (game->plr.dir_y
	* spr->sprt_x - game->plr.dir_x * spr->sprt_y);
	spr->trform_y = spr->inv_det * (-game->plr.plane_y
	* spr->sprt_x + game->plr.plane_x * spr->sprt_y);
	spr->sprt_scr_x = (int)((W / 2) * (1 + spr->trform_x / spr->trform_y));
	spr->sprt_h = abs((int)(H / (spr->trform_y)));
	spr->drw_start_y = -(spr->sprt_h) / 2 + H / 2;
	if (spr->drw_start_y < 0)
		spr->drw_start_y = 0;
	spr->drw_end_y = spr->sprt_h / 2 + H / 2;
	if (spr->drw_end_y >= H)
		spr->drw_end_y = H;
	spr->sprt_w = abs((int)(H / (spr->trform_y)));
	spr->drw_start_x = -(spr->sprt_w) / 2 + spr->sprt_scr_x;
	if (spr->drw_start_x < 0)
		spr->drw_start_x = 0;
	spr->drw_end_x = spr->sprt_w / 2 + spr->sprt_scr_x;
	if (spr->drw_end_x >= W)
		spr->drw_end_x = W;
	spr->strp = spr->drw_start_x;
}

void	draw_sprites(t_game *game, int s)
{
	t_sprt	spr;

	while (s < game->scount)
	{
		draw_spr_prepare(&spr, game, s);
		while (spr.strp < spr.drw_end_x)
		{
			spr.tex_x = (int)(256 * (spr.strp - (-(spr.sprt_w) / 2
					+ spr.sprt_scr_x)) * TEXWIDTH / spr.sprt_w) / 256;
			if (spr.trform_y > 0 && spr.strp > 0 && spr.strp < W
			&& spr.trform_y < (game->z_buffer)[spr.strp])
			{
				spr.y = spr.drw_start_y;
				draw_put_sprites(&spr, game);
			}
			spr.strp++;
		}
		s++;
	}
}
