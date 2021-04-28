/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 21:57:48 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/04/26 22:28:49 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_plane(t_mprm *mprm)
{
	if (mprm->plr.dir == 'N')
	{
		mprm->plr.planeX = 0.66;
		mprm->plr.planeY = 0.0;
	}
	else if (mprm->plr.dir == 'S')
	{
		mprm->plr.planeX = -0.66;
		mprm->plr.planeY = 0.0;
	}
	else if (mprm->plr.dir == 'E')
	{
		mprm->plr.planeX = 0.0;
		mprm->plr.planeY = -0.66;
	}
	else if (mprm->plr.dir == 'W')
	{
		mprm->plr.planeX = 0.0;
		mprm->plr.planeY = 0.66;
	}
}

void	player_dir(t_mprm *mprm)
{
	if (mprm->plr.dir == 'N')
	{
		mprm->plr.dirX = 0.0;
		mprm->plr.dirY = 1.0;
	}
	else if (mprm->plr.dir == 'S')
	{
		mprm->plr.dirX = 0.0;
		mprm->plr.dirY = -1.0;
	}
	else if (mprm->plr.dir == 'E')
	{
		mprm->plr.dirX = 1.0;
		mprm->plr.dirY = 0.0;
	}
	else if (mprm->plr.dir == 'W')
	{
		mprm->plr.dirX = -1.0;
		mprm->plr.dirY = 0.0;
	}
	player_plane(mprm);
}

void 	player_position(int x, int y, t_mprm *mprm)
{
	mprm->plr.posX = x + 0.5;
	mprm->plr.posY = y + 0.5;
	mprm->plr.dir = mprm->map.mp[y][x];
	player_dir(mprm);
}
