/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_body.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 02:36:24 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/03/23 21:17:21 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_path(t_mprm *mprm, char *str, char mode, int len)
{
	char	*filename;

	if (!(filename = (char *)ft_calloc(len + 1, sizeof(char))))
		return (red_flag(-1, mprm));
	filename = ft_strcpy(filename, str);
	if (mode == 'N')
		mprm->paths.no = filename;
	else if (mode == 'W')
		mprm->paths.we = filename;
	else if (mode == 'E')
		mprm->paths.ea = filename;
	else if (mode == 'O')
		mprm->paths.so = filename;
	else if (mode == 'S')
		mprm->paths.sp = filename;
	else
		return (red_flag(-1, mprm));
	return (1);
}

int		parse_pth(t_mprm *mprm, char **str, char mode, int len)
{
	int		fd;
	int		max_idx;

	(*str)++;
	if (*(*str) != 32 || get_chk(mprm, mode))
		return (red_flag(-1, mprm));
	while (*(*str)== 32)
		(*str)++;
	max_idx = trim_space_end(str);
	if ((*str)[max_idx] != 'm' || (*str)[max_idx - 1] != 'p'
	|| (*str)[max_idx - 2] != 'x' || (*str)[max_idx - 3] != '.'
	|| ft_isalnum((*str)[max_idx - 4]) == 0)
		return (red_flag(-1, mprm));
	if ((fd = open(*str, O_RDONLY)) < 0)
		return (red_flag(-1, mprm));
	close(fd);
	return (red_flag(init_path(mprm, *str, mode, len), mprm));
}

int		parse_clr(t_mprm *mprm, char **str, char mode, int *fl)
{
	int	result;

	*fl = *fl - (*fl % 10);
	*fl += 10;
	if ((result = fill_num(str, 3)) < 0)
		return (red_flag(-1, mprm));
	if (mode == 'F')
	{
		if (mprm->colors.floor_color.r < 0)
			mprm->colors.floor_color.r = result;
		else if (mprm->colors.floor_color.g < 0)
			mprm->colors.floor_color.g = result;
		else if (mprm->colors.floor_color.b < 0)
			mprm->colors.floor_color.b = result;
	}
	if (mode == 'C')
	{
		if (mprm->colors.cell_color.r < 0)
			mprm->colors.cell_color.r = result;
		else if (mprm->colors.cell_color.g < 0)
			mprm->colors.cell_color.g = result;
		else if (mprm->colors.cell_color.b < 0)
			mprm->colors.cell_color.b = result;
	}
	return (1);
}

int		parse_resolut(t_mprm *mprm, char **line)
{
	int fl;

	(*line)++;
	if (*(*line) != 32 || get_chk(mprm, 'R'))
		return (red_flag(-1, mprm));
	trim_space_end(line);
	fl = 0;
	while (*(*line))
	{
		if (*(*line) == 32)
			(*line)++;
		else if (*(*line) >= '0' && *(*line) <= '9')
		{
			fl++;
			if (mprm->resolution.x == -1)
				mprm->resolution.x = fill_num(line, 10);
			else if (mprm->resolution.y == -1)
				mprm->resolution.y = fill_num(line, 10);
		}
		else
			return (red_flag(-1, mprm));
	}
	if (mprm->resolution.x < 1 || mprm->resolution.y < 1 || fl > 2)
		return (red_flag(-1, mprm));
	return (1);
}
