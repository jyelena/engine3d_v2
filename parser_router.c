/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 18:41:43 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/03/27 23:36:47 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_chk(t_game *game, char mode)
{
	if (mode == 'N')
		return (game->chk.no);
	else if (mode == 'W')
		return (game->chk.we);
	else if (mode == 'E')
		return (game->chk.ea);
	else if (mode == 'O')
		return (game->chk.so);
	else if (mode == 'S')
		return (game->chk.sp);
	else if (mode == 'F')
		return (game->chk.f);
	else if (mode == 'C')
		return (game->chk.c);
	else if (mode == 'R')
		return (game->chk.r);
	return (1);
}

int		set_chk(int result, t_game *game, char mode)
{
	if (mode == 'N')
		game->chk.no = result;
	else if (mode == 'W')
		game->chk.we = result;
	else if (mode == 'E')
		game->chk.ea = result;
	else if (mode == 'O')
		game->chk.so = result;
	else if (mode == 32)
		game->chk.sp = result;
	else if (mode == 'F')
		game->chk.f = result;
	else if (mode == 'C')
		game->chk.c = result;
	else if (mode == 'R')
		game->chk.r = result;
	return (result);
}

int		parse_clr_rout(t_game *game, char **str, char mode)
{
	int		fl;

	(*str)++;
	if (*(*str) != 32 || get_chk(game, mode))
		wrt_err("Invalid params", 1, game, NULL);
	trim_space_end(str);
	fl = 0;
	while (*(*str))
	{
		if (*(*str) == 32)
			(*str)++;
		else if (*(*str) == ',' && fl % 10 == 0)
		{
			fl += 1;
			(*str)++;
		}
		else if (*(*str) >= '0' && *(*str) <= '9')
			parse_clr(game, str, mode, &fl);
		else
			wrt_err("Invalid params", 1, game, NULL);
		if (fl > 30 || fl == 1 || fl % 10 > 1)
			wrt_err("Invalid params", 1, game, NULL);
	}
	return (1);
}

int		parse_pth_rout(t_game *game, char **str, int len)
{
	char mode;

	if (*(*str) == 32)
		(*str)--;
	mode = *(*str);
	if (((*str)[0] == 'N' && (*str)[1] != 'O')
	|| ((*str)[0] == 'W' && (*str)[1] != 'E')
	|| ((*str)[0] == 'E' && (*str)[1] != 'A')
	|| ((*str)[0] == 'O' && (*str)[1] != 32)
	|| ((*str)[0] == 'S' && (*str)[1] != 32))
		wrt_err("Invalid params", 1, game, NULL);
	if (mode == 'N' || mode == 'W' || mode == 'E')
		(*str)++;
	return (parse_pth(game, str, mode, len));
}

int		prs_rout(t_game *game, char *line)
{
	int		len;
	char	mode;

	len = trim_space(&line);
	if (ft_strlen(line) == 1)
		wrt_err("Invalid params", 1, game, NULL);
	mode = *line;
	if (*line == 'R')
		return (set_chk(parse_resolut(game, &line), game, mode));
	else if (*line == 'F' || *line == 'C')
		return (set_chk(parse_clr_rout(game, &line, *line), game, mode));
	else if (*line == 'N' || *line == 'W' || *line == 'E')
		return (set_chk(parse_pth_rout(game, &line, len), game, mode));
	else if (*line == 'S')
	{
		line++;
		mode = *line;
		if (*line == 'O' || *line == 32)
			return (set_chk(parse_pth_rout(game, &line, len), game, mode));
	}
	else if (!*line)
		return (0);
	wrt_err("Invalid params", 1, game, NULL);
	return (0);
}
