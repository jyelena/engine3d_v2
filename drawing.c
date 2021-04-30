/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:30:40 by jyelena           #+#    #+#             */
/*   Updated: 2021/04/30 06:24:47 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->data.addr + (y * game->data.line_length + x
	* (game->data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_f_c(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y <= H / 2)
	{
		x = 0;
		while (x < W)
			my_mlx_pixel_put(game, x++, y, game->colors.ceil_color.rgb);
		y++;
	}
	while (y < H)
	{
		x = 0;
		while (x < W)
			my_mlx_pixel_put(game, x++, y, game->colors.floor_color.rgb);
		y++;
	}
}

void	draw_magic(t_game *game, int sshot_flg, int x)
{
	draw_f_c(game);
	while (++x < W)
	{
		draw_ray_calc(game, x);
		draw_side_hit_calc(game, x);
		draw_until_hit(game, x);
		draw_calc_per_ray(game, x);
		draw_lohi_pix_calc(game, x);
		draw_env(game, x);
		(game->z_buffer)[x] = game->ray.perp_wall_dist;
	}
	draw_sprites(game, 0);
	if (!sshot_flg)
	{
		mlx_put_image_to_window(game->data.mlx, game->data.win, game->data.img,
		0, 0);
		mlx_destroy_image(game->data.mlx, game->data.img);
		game->data.img = mlx_new_image(game->data.mlx, W, H);
		game->data.addr = mlx_get_data_addr(game->data.img,
		&game->data.bits_per_pixel, &game->data.line_length,
		&game->data.endian);
	}
}

void	draw_init(t_game *game, int sshot_flg)
{
	game->data.mlx = mlx_init();
	get_screen_size(game, sshot_flg);
	game->z_buffer = (double *)malloc(sizeof(double) * W);
	if (!sshot_flg)
		game->data.win = mlx_new_window(game->data.mlx, W, H, "");
	game->data.img = mlx_new_image(game->data.mlx, W, H);
	game->data.addr = mlx_get_data_addr(game->data.img,
	&game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);
	take_textures(game);
	take_tex_addr(game);
	draw_magic(game, sshot_flg, -1);
}

void	live_game(t_game *game)
{
	mlx_hook(game->data.win, 2, (1L << 0), &key_press, game);
	mlx_hook(game->data.win, 3, (1L << 1), &key_release, game);
	mlx_hook(game->data.win, 17, 0, &close_win, game);
	mlx_loop_hook(game->data.mlx, &moving, game);
	mlx_loop(game->data.mlx);
}
