/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:29:40 by jyelena           #+#    #+#             */
/*   Updated: 2021/04/30 15:24:27 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void
	get_color(t_game *game)
{
	game->colors.ceil_color.rgb = create_rgb(game->colors.ceil_color.r,
			game->colors.ceil_color.g, game->colors.ceil_color.b);
	game->colors.floor_color.rgb = create_rgb(game->colors.floor_color.r,
			game->colors.floor_color.g, game->colors.floor_color.b);
}

unsigned int
	*take_pixel(t_tex tex, int x, int y)
{
	return ((unsigned int *)(tex.timg.addr + (y * tex.timg.linelen + x
			* (tex.timg.bpp / 8))));
}

void
	take_textures(t_game *game)
{
	game->tex.no.timg.img = mlx_xpm_file_to_image(game->data.mlx,
			game->paths.no, &(game->tex.no.w), &(game->tex.no.h));
	game->tex.so.timg.img = mlx_xpm_file_to_image(game->data.mlx,
			game->paths.so, &(game->tex.so.w), &(game->tex.so.h));
	game->tex.ea.timg.img = mlx_xpm_file_to_image(game->data.mlx,
			game->paths.ea, &(game->tex.ea.w), &(game->tex.ea.h));
	game->tex.we.timg.img = mlx_xpm_file_to_image(game->data.mlx,
			game->paths.we, &(game->tex.we.w), &(game->tex.we.h));
	game->tex.sp.timg.img = mlx_xpm_file_to_image(game->data.mlx,
			game->paths.sp, &(game->tex.sp.w), &(game->tex.sp.h));
	check_textures(game);
}

void
	take_tex_addr(t_game *game)
{
	game->tex.no.timg.addr = mlx_get_data_addr(game->tex.no.timg.img,
			&(game->tex.no.timg.bpp), &(game->tex.no.timg.linelen),
			&(game->tex.no.timg.endian));
	game->tex.so.timg.addr = mlx_get_data_addr(game->tex.so.timg.img,
			&(game->tex.so.timg.bpp), &(game->tex.so.timg.linelen),
			&(game->tex.so.timg.endian));
	game->tex.ea.timg.addr = mlx_get_data_addr(game->tex.ea.timg.img,
			&(game->tex.ea.timg.bpp), &(game->tex.ea.timg.linelen),
			&(game->tex.ea.timg.endian));
	game->tex.we.timg.addr = mlx_get_data_addr(game->tex.we.timg.img,
			&(game->tex.we.timg.bpp), &(game->tex.we.timg.linelen),
			&(game->tex.we.timg.endian));
	game->tex.sp.timg.addr = mlx_get_data_addr(game->tex.sp.timg.img,
			&(game->tex.sp.timg.bpp), &(game->tex.sp.timg.linelen),
			&(game->tex.sp.timg.endian));
}
