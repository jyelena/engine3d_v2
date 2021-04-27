/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 22:05:01 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/04/26 22:25:53 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_sprites_struct(t_mprm *mprm)
{
	int	x;
	int	y;
	int	z;

	z = 0;
	y = 0;
	while (mprm->map.mp[y])
	{
		x = 0;
		while (mprm->map.mp[y][x])
		{
			if (mprm->map.mp[y][x] == '2')
			{
				(mprm->spr)[z].x = x + 0.5;
				(mprm->spr)[z].y = y + 0.5;
				z++;
			}
			x++;
		}
		y++;
	}
}