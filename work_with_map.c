/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 02:08:55 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/03/28 01:21:01 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		chk_on_top(int y, int x, t_mprm *mprm)
{
	if (!(mprm->map.mp[y - 1][x] == 32 || mprm->map.mp[y - 1][x] == 49
	|| mprm->map.mp[y - 1][x] == 0))
		return (-2);
	if (x > 0 && !(mprm->map.mp[y - 1][x - 1] == 32
	|| mprm->map.mp[y - 1][x - 1] == 49 || mprm->map.mp[y - 1][x - 1] == 0))
		return (-2);
	if (x < mprm->map.w - 1 && !(mprm->map.mp[y - 1][x + 1] == 32
	|| mprm->map.mp[y - 1][x + 1] == 49 || mprm->map.mp[y - 1][x + 1] == 0))
		return (-2);
	return (1);
}

int		chk_on_bottom(int y, int x, t_mprm *mprm)
{
	if (!(mprm->map.mp[y + 1][x] == 32 || mprm->map.mp[y + 1][x] == 49
	|| mprm->map.mp[y + 1][x] == 0))
		return (-2);
	if (x > 0 && !(mprm->map.mp[y + 1][x - 1] == 32
	|| mprm->map.mp[y + 1][x - 1] == 49 || mprm->map.mp[y + 1][x - 1] == 0))
		return (-2);
	if (x < mprm->map.w - 1 && !(mprm->map.mp[y + 1][x + 1] == 32
	|| mprm->map.mp[y + 1][x + 1] == 49 || mprm->map.mp[y + 1][x + 1] == 0))
		return (-2);
	return (1);
}

int		chk_round(int y, int x, t_mprm *mprm)
{
	if ((y > 0 && chk_on_top(y, x, mprm) < 0)
	|| (y < mprm->map.d - 1 && chk_on_bottom(y, x, mprm) < 0))
		return (-2);
	if (x > 0 && !(mprm->map.mp[y][x - 1] == 32 || mprm->map.mp[y][x - 1] == 49
	|| mprm->map.mp[y][x - 1] == 0))
		return (-2);
	if (x < mprm->map.w - 1 && !(mprm->map.mp[y][x + 1] == 32
	|| mprm->map.mp[y][x + 1] == 49 || mprm->map.mp[y][x + 1] == 0))
		return (-2);
	if (mprm->map.mp[y][x] == 'N' || mprm->map.mp[y][x] == 'S'
	|| mprm->map.mp[y][x] == 'W' || mprm->map.mp[y][x] == 'E')
	{
		mprm->player.x = x;
		mprm->player.y = y;
		mprm->player.dir = mprm->map.mp[y][x];
	}
	return (1);
}

int		valid_map(t_mprm *mprm)
{
	int y;
	int x;

	y = 0;
	while (y < mprm->map.d)
	{
		x = 0;
		while (x < mprm->map.w)
		{
			if (mprm->map.mp[y][x] == ' ')
			{
				if (chk_round(y, x, mprm) < 0)
					return (red_flag(-2, mprm));
			}
			x++;
		}
		y++;
	}
	return (1);
}

int		make_map(t_mprm *mprm, t_list **tmp_map)
{
	int		d;
	t_list	*tmp;

	tmp = *tmp_map;
	d = 0;
	while ((*tmp_map) && d < mprm->map.d - 1)
	{
		mprm->map.mp[d] = (char *)ft_memset((void *)mprm->map.mp[d], 32,
		mprm->map.w);
		if (d > 0 && d < mprm->map.d - 1)
		{
			line_cpy(tmp->content, &mprm->map.mp[d], mprm);
			tmp = tmp->next;
		}
		printf("|%s|\n", mprm->map.mp[d]);
		d++;
	}
	mprm->map.mp[d] = (char *)ft_memset((void *)mprm->map.mp[d], 32,
	mprm->map.w);
	printf("|%s|\n", mprm->map.mp[d]);
	free_list(tmp_map);
	return (1);
}
