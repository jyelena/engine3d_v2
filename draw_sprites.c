/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:29:57 by jyelena           #+#    #+#             */
/*   Updated: 2021/04/28 19:30:00 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprites(t_game *game, int x, double **z_buffer)
{
	int s;
	double sprt_x;
	double sprt_y;
	double inv_det;
	double transform_x;
	double transform_y;
	int sprt_scr_x;
	int sprt_h;
	int drw_start_y;
	int drw_end_y;
	int sprt_w;
	int drw_start_x;
	int drw_end_x;
	int stripe;

	*z_buffer[x] = game->ray.perp_wall_dist;
	s = 0;
	while (s < game->scount)
	{
		sprt_x = (game->spr)[s].x - game->plr.pos_x + 0.5;
		sprt_y = (game->spr)[s].y - game->plr.pos_y + 0.5;
		inv_det = 1.0 / (game->plr.plane_x * game->plr.dir_y
		- game->plr.dir_x * game->plr.plane_y);
		transform_x = inv_det * (game->plr.dir_y
		* sprt_x - game->plr.dir_x * sprt_y);
		transform_y = inv_det * (-game->plr.plane_y
		* sprt_x + game->plr.plane_x * sprt_y);
		sprt_scr_x = (int)((W / 2) * (1 + transform_x / transform_y));
		sprt_h = abs((int)(H / (transform_y)));
		drw_start_y = -sprt_h / 2 + H / 2;
		if (drw_start_y < 0)
			drw_start_y = 0;
		drw_end_y = sprt_h / 2 + H / 2;
		if (drw_end_y >= H)
			drw_end_y = H;
		sprt_w = abs( (int) (H / (transform_y)));
		drw_start_x = -sprt_w / 2 + sprt_scr_x;
		if (drw_start_x < 0)
			drw_start_x = 0;
		drw_end_x = sprt_w / 2 + sprt_scr_x;
		if (drw_end_x >= W)
			drw_end_x = W;
		stripe = drw_start_x;
		while (stripe < drw_end_x)
		{
			int tex_x = (int)(256 * (stripe - (-sprt_w / 2
			+ sprt_scr_x)) * texWidth / sprt_w) / 256;
			if (transform_y > 0 && stripe > 0 && stripe < W && transform_y
					< *z_buffer[stripe])
			{
				int y = drw_start_y;
				while (y < drw_end_y)
				{
					int d = (y) * 256 - H * 128 + sprt_h * 128;
					int tex_y = ((d * texHeight) / sprt_h) / 256;
//					color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
//					if((color & 0x00FFFFFF) != 0)
//						z_buffer[y][stripe] = color;
					y++;
				}
			}
			stripe++;
		}
	}
}
