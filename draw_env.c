/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:29:23 by jyelena           #+#    #+#             */
/*   Updated: 2021/04/28 19:29:28 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_env(t_game *game, int x)
{
	t_tex ptex;
	int y;

	y = game->ray.draw_start;
	while ( y < game->ray.draw_end)
	{
		if (game->ray.side == 0 && game->ray.step_x > 0)
			ptex = game->tex.ea;
		else if (game->ray.side == 0 && game->ray.step_x < 0)
			ptex = game->tex.we;
		else if (game->ray.side == 1 && game->ray.step_y > 0)
			ptex = game->tex.so;
		else
			ptex = game->tex.no;
		game->ray.tex_y = (int)game->ray.tex_pos & (texHeight - 1);
		game->ray.tex_pos += game->ray.step;
		game->ray.color = take_pixel(ptex, game->ray.tex_x, game->ray.tex_y);
		my_mlx_pixel_put(game, x, y, (int)(*game->ray.color));
		y++;
	}
}

void	draw_calc_wall(t_game *game, int x)
{
	if(game->ray.side == 0)
		game->ray.wall_x = game->plr.pos_y
				+ game->ray.perp_wall_dist * game->ray.ray_dir_y;
	else
		game->ray.wall_x = game->plr.pos_x
				+ game->ray.perp_wall_dist * game->ray.ray_dir_x;
	game->ray.wall_x -= floor((game->ray.wall_x));
}

void	draw_coord_calc(t_game *game, int x)
{
	game->ray.tex_x = (int)(game->ray.wall_x * (double)texWidth);
	if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
		game->ray.tex_x = texWidth - game->ray.tex_x - 1;
	if (game->ray.side == 1 && game->ray.ray_dir_y < 0)
		game->ray.tex_x = texWidth - game->ray.tex_x - 1;
	game->ray.step = 1.0 * texHeight / game->ray.line_h;
	game->ray.tex_pos = (game->ray.draw_start - H / 2.0
	+ game->ray.line_h / 2.0) * game->ray.step;
}
