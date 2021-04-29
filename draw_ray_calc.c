/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_calc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:31:00 by jyelena           #+#    #+#             */
/*   Updated: 2021/04/28 19:31:02 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ray_calc(t_game *game, int x)
{
	game->ray.camera_x = 2 * x / (double)W - 1;
	game->ray.ray_dir_x = game->plr.dir_x + game->plr.plane_x
											* game->ray.camera_x;
	game->ray.ray_dir_y = game->plr.dir_y + game->plr.plane_y
											* game->ray.camera_x;
	game->ray.map_x = (int)game->plr.pos_x;
	game->ray.map_y = (int)game->plr.pos_y;
	if (game->ray.ray_dir_y == 0)
		game->ray.delta_dist_x = 0;
	else
	{
		if (game->ray.ray_dir_x == 0)
			game->ray.delta_dist_x = 1;
		else
			game->ray.delta_dist_x = fabs(1 / game->ray.ray_dir_x);
	}
	if (game->ray.ray_dir_x == 0)
		game->ray.delta_dist_y = 0;
	else
	{
		if (game->ray.ray_dir_y == 0)
			game->ray.delta_dist_y = 1;
		else
			game->ray.delta_dist_y = fabs(1 / game->ray.ray_dir_y);
	}
}

void	draw_side_hit_calc(t_game *game, int x)
{
	game->ray.side_dist_x = 0;
	if (game->ray.ray_dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist_x = (game->plr.pos_x - game->ray.map_x)
								* game->ray.delta_dist_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->plr.pos_x)
								* game->ray.delta_dist_x;
	}
	if (game->ray.ray_dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist_y = (game->plr.pos_y - game->ray.map_y)
								* game->ray.delta_dist_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist_y = (game->ray.map_y + 1.0 - game->plr.pos_y)
								* game->ray.delta_dist_y;
	}
}

void	draw_until_hit(t_game *game, int x)
{
	while (game->ray.hit == 0)
	{
		if (game->ray.side_dist_x < game->ray.side_dist_y)
		{
			game->ray.side_dist_x += game->ray.delta_dist_x;
			game->ray.map_x += game->ray.step_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_dist_y += game->ray.delta_dist_y;
			game->ray.map_y += game->ray.step_y;
			game->ray.side = 1;
		}
		if (PMAP[game->ray.map_y][game->ray.map_x] == '1')
			game->ray.hit = 1;
	}
}

void	draw_calc_per_ray(t_game *game, int x)
{
	if (game->ray.side == 0)
	{
		game->ray.perp_wall_dist = (game->ray.map_x - game->plr.pos_x
									+ (1.0 - game->ray.step_x) / 2) / game->ray
											.ray_dir_x;
	}
	else
	{
		game->ray.perp_wall_dist = (game->ray.map_y - game->plr.pos_y
									+ (1.0 - game->ray.step_y) / 2) / game->ray
											.ray_dir_y;
	}
	game->ray.line_h = (int)(H / game->ray.perp_wall_dist);
}

void	draw_lohi_pix_calc(t_game *game, int x)
{
	game->ray.draw_start = -game->ray.line_h / 2 + H / 2;
	if(game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.line_h / 2 + H / 2;
	if(game->ray.draw_end >= H)
		game->ray.draw_end = H;
	game->ray.tex_num = PMAP[game->ray.map_y][game->ray.map_x] - 1;
}
