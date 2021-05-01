/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_body.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 02:36:24 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/03/27 23:55:22 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	chk_coma(int *fl)
{
	if (*fl > 0 && (*fl - 1) % 10 != 0)
		wrt_err("Invalid color params", 1);
	*fl = *fl - (*fl % 10);
	*fl += 10;
}

int		init_path(t_game *game, char *str, char mode, int len)
{
	char	*filename;

	if (!(filename = (char *)ft_calloc(len + 1, sizeof(char))))
		return (red_flag(-1, game));
	filename = ft_strcpy(filename, str);
	if (mode == 'N')
		game->paths.no = filename;
	else if (mode == 'W')
		game->paths.we = filename;
	else if (mode == 'E')
		game->paths.ea = filename;
	else if (mode == 'O')
		game->paths.so = filename;
	else if (mode == 'S')
		game->paths.sp = filename;
	else
		return (red_flag(-1, game));
	return (1);
}

int		parse_pth(t_game *game, char **str, char mode, int len)
{
	int		fd;
	int		max_idx;

	(*str)++;
	if (*(*str) != 32 || get_chk(game, mode))
		return (red_flag(-13, game));
	while (*(*str) == 32)
		(*str)++;
	max_idx = trim_space_end(str);
	if ((*str)[max_idx] != 'm' || (*str)[max_idx - 1] != 'p'
	|| (*str)[max_idx - 2] != 'x' || (*str)[max_idx - 3] != '.'
	|| ft_isalnum((*str)[max_idx - 4]) == 0)
		return (red_flag(-13, game));
	if ((fd = open(*str, O_RDONLY)) < 0)
		return (red_flag(-13, game));
	close(fd);
	return (init_path(game, *str, mode, len));
}

int		parse_clr(t_game *game, char **str, char mode, int *fl)
{
	int	result;

	chk_coma(fl);
	if ((result = fill_num(str, 3)) < 0)
		return (red_flag(-11, game));
	if (mode == 'F')
	{
		if (game->colors.floor_color.r < 0)
			game->colors.floor_color.r = result;
		else if (game->colors.floor_color.g < 0)
			game->colors.floor_color.g = result;
		else if (game->colors.floor_color.b < 0)
			game->colors.floor_color.b = result;
	}
	if (mode == 'C')
	{
		if (game->colors.ceil_color.r < 0)
			game->colors.ceil_color.r = result;
		else if (game->colors.ceil_color.g < 0)
			game->colors.ceil_color.g = result;
		else if (game->colors.ceil_color.b < 0)
			game->colors.ceil_color.b = result;
	}
	return (1);
}

int		parse_resolut(t_game *game, char **line)
{
	int fl;

	(*line)++;
	if (*(*line) != 32 || get_chk(game, 'R'))
		return (red_flag(-12, game));
	trim_space_end(line);
	fl = 0;
	while (*(*line))
	{
		if (*(*line) == 32)
			(*line)++;
		else if (*(*line) >= '0' && *(*line) <= '9' && fl <= 2)
		{
			fl++;
			if (game->resolution.x == -1)
				game->resolution.x = fill_num(line, 10);
			else if (game->resolution.y == -1)
				game->resolution.y = fill_num(line, 10);
		}
		else
			return (red_flag(-12, game));
	}
	if (game->resolution.x < 1 || game->resolution.y < 1 || fl > 2)
		return (red_flag(-12, game));
	return (1);
}
