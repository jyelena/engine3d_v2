/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:29:23 by jyelena           #+#    #+#             */
/*   Updated: 2021/05/01 03:49:21 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_textures(t_game *game)
{
	if (game->tex.ea.timg.img == NULL || game->tex.ea.w != 64 || game->tex.ea.h
	!= 64)
		wrt_err("Crached east textures", 1);
	if (game->tex.we.timg.img == NULL || game->tex.we.w != 64 || game->tex.we.h
	!= 64)
		wrt_err("Crached west textures", 1);
	if (game->tex.no.timg.img == NULL || game->tex.no.w != 64 || game->tex.no.h
	!= 64)
		wrt_err("Crached north textures", 1);
	if (game->tex.so.timg.img == NULL || game->tex.so.w != 64 || game->tex.so.h
	!= 64)
		wrt_err("Crached south textures", 1);
	if (game->tex.sp.timg.img == NULL || game->tex.sp.w != 64 || game->tex.sp.h
	!= 64)
		wrt_err("Crached sprite textures", 1);
}

void	draw_env(t_game *game, int x)
{
	t_tex	ptex;
	int		y;

	draw_calc_wall(game, x);
	draw_coord_calc(game, x);
	y = game->ray.draw_start;
	while (y < game->ray.draw_end)
	{
		if (game->ray.side == 0 && game->ray.step_x > 0)
			ptex = game->tex.ea;
		else if (game->ray.side == 0 && game->ray.step_x < 0)
			ptex = game->tex.we;
		else if (game->ray.side == 1 && game->ray.step_y > 0)
			ptex = game->tex.so;
		else
			ptex = game->tex.no;
		game->ray.tex_y = (int)game->ray.tex_pos & (TEXHEIGH - 1);
		game->ray.tex_pos += game->ray.step;
		game->ray.color = take_pixel(ptex, game->ray.tex_x, game->ray.tex_y);
		my_mlx_pixel_put(game, x, y, (int)(*game->ray.color));
		y++;
	}
}

void	draw_calc_wall(t_game *game, int x)
{
	if (game->ray.side == 0)
		game->ray.wall_x = game->plr.pos_y
				+ game->ray.perp_wall_dist * game->ray.ray_dir_y;
	else
		game->ray.wall_x = game->plr.pos_x
				+ game->ray.perp_wall_dist * game->ray.ray_dir_x;
	game->ray.wall_x -= floor((game->ray.wall_x));
}

void	draw_coord_calc(t_game *game, int x)
{
	game->ray.tex_x = (int)(game->ray.wall_x * (double)TEXWIDTH);
	if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
		game->ray.tex_x = TEXWIDTH - game->ray.tex_x - 1;
	if (game->ray.side == 1 && game->ray.ray_dir_y < 0)
		game->ray.tex_x = TEXWIDTH - game->ray.tex_x - 1;
	game->ray.step = 1.0 * TEXHEIGH / game->ray.line_h;
	game->ray.tex_pos = (game->ray.draw_start - H / 2.0
	+ game->ray.line_h / 2.0) * game->ray.step;
}
