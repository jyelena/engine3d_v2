/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_screenshot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 06:38:29 by jyelena           #+#    #+#             */
/*   Updated: 2021/04/30 06:39:17 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_screen_size(t_game *game, int sshot_flg)
{
	int x;
	int y;

	mlx_get_screen_size(game->data.mlx, &x, &y);
	if (sshot_flg)
	{
		if (game->resolution.x > 10000)
			game->resolution.x = 10000;
		if (game->resolution.y > 10000)
			game->resolution.y = 10000;
	}
	else
	{
		if (game->resolution.x > x)
			game->resolution.x = x;
		if (game->resolution.y > y)
			game->resolution.y = y;
	}
}

void	create_file_head(t_fname *file, int sshot_size)
{
	unsigned char file_head[14];

	ft_bzero(file_head, 14);
	file_head[0] = (unsigned char)('B');
	file_head[1] = (unsigned char)('M');
	file_head[2] = (unsigned char)(sshot_size);
	file_head[3] = (unsigned char)(sshot_size >> 8);
	file_head[4] = (unsigned char)(sshot_size >> 16);
	file_head[5] = (unsigned char)(sshot_size >> 24);
	file_head[10] = (unsigned char)(54);
	write(file->fd, file_head, 14);
}

void	create_file_body(t_fname *file, t_game *game)
{
	unsigned char file_body[40];

	ft_bzero(file_body, 40);
	file_body[0] = (unsigned char)(40);
	file_body[4] = (unsigned char)(game->resolution.x);
	file_body[5] = (unsigned char)(game->resolution.x >> 8);
	file_body[6] = (unsigned char)(game->resolution.x >> 16);
	file_body[7] = (unsigned char)(game->resolution.x >> 24);
	file_body[8] = (unsigned char)(game->resolution.y);
	file_body[9] = (unsigned char)(game->resolution.y >> 8);
	file_body[10] = (unsigned char)(game->resolution.y >> 16);
	file_body[11] = (unsigned char)(game->resolution.y >> 24);
	file_body[12] = (unsigned char)(1);
	file_body[14] = (unsigned char)(32);
	write(file->fd, file_body, 40);
}

void	take_screenshot(t_game *game, t_fname *file)
{
	int		sshot_size;
	int		height;
	int		line_len;

	file->fd = open(file->name, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG);
	draw_magic(game, 1, -1);
	sshot_size = 14 + 40 + (4 * game->resolution.y * game->resolution.x);
	create_file_head(file, sshot_size);
	create_file_body(file, game);
	height = game->resolution.y;
	line_len = game->resolution.x * game->data.bits_per_pixel / 8;
	while (height >= 0)
	{
		write(file->fd, (unsigned char *)(game->data.addr + height *
		game->data.line_length), line_len);
		height--;
	}
	close(file->fd);
	mlx_destroy_image(game->data.mlx, game->data.img);
	game->data.img = mlx_new_image(game->data.mlx, W, H);
	game->data.addr = mlx_get_data_addr(game->data.img,
	&game->data.bits_per_pixel, &game->data.line_length,
	&game->data.endian);
}
