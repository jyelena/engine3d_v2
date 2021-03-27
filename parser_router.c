/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 18:41:43 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/03/27 19:00:38 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_chk(t_mprm *mprm, char mode)
{
	if (mode == 'N')
		return (mprm->chk.no);
	else if (mode == 'W')
		return (mprm->chk.we);
	else if (mode == 'E')
		return (mprm->chk.ea);
	else if (mode == 'O')
		return (mprm->chk.so);
	else if (mode == 'S')
		return (mprm->chk.sp);
	else if (mode == 'F')
		return (mprm->chk.f);
	else if (mode == 'C')
		return (mprm->chk.c);
	else if (mode == 'R')
		return (mprm->chk.r);
	return (1);
}

int		set_chk(int result, t_mprm *mprm, char mode)
{
	if (mode == 'N')
		mprm->chk.no = red_flag(result, mprm);
	else if (mode == 'W')
		mprm->chk.we = red_flag(result, mprm);
	else if (mode == 'E')
		mprm->chk.ea = red_flag(result, mprm);
	else if (mode == 'O')
		mprm->chk.so = red_flag(result, mprm);
	else if (mode == 32)
		mprm->chk.sp = red_flag(result, mprm);
	else if (mode == 'F')
		mprm->chk.f = red_flag(result, mprm);
	else if (mode == 'C')
		mprm->chk.c = red_flag(result, mprm);
	else if (mode == 'R')
		mprm->chk.r = red_flag(result, mprm);
	return (result);
}

int		parse_clr_rout(t_mprm *mprm, char **str, char mode)
{
	int		fl;

	(*str)++;
	if (*(*str) != 32 || get_chk(mprm, mode))
		return (red_flag(-1, mprm));
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
			parse_clr(mprm, str, mode, &fl);
		else
			return (red_flag(-1, mprm));
		if (fl > 30 || fl == 1 || fl % 10 > 1)
			return (red_flag(-1, mprm));
	}
	return (1);
}

int		parse_pth_rout(t_mprm *mprm, char **str, int len)
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
			return (red_flag(-1, mprm));
	if (mode == 'N' || mode == 'W' || mode == 'E')
		(*str)++;
	return (red_flag(parse_pth(mprm, str, mode, len), mprm));
}

int		prs_rout(t_mprm *mprm, char *line)
{
	int	len;

	len = trim_space(&line);
	if (ft_strlen(line) == 1)
		return (red_flag(-1, mprm));
	while (*line == 32)
		line++;
	if (*line == 'R')
		return (set_chk(parse_resolut(mprm, &line), mprm, *line));
	else if (*line == 'F' || *line == 'C')
		return (set_chk(parse_clr_rout(mprm, &line, *line), mprm, *line));
	else if (*line == 'N' || *line == 'W' || *line == 'E')
		return (set_chk(parse_pth_rout(mprm, &line, len), mprm, *line));
	else if (*line == 'S')
	{
		line++;
		if (*line == 'O' || *line == 32)
			return (set_chk(parse_pth_rout(mprm, &line, len), mprm, *line));
	}
	else if (!*line)
		return (0);
	return (red_flag(-1, mprm));
}
