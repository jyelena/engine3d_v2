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

void	player_dir(t_mprm *mprm)
{
	if (mprm->player.dir == 'N')
	{
		mprm->player.dirX = 0;
		mprm->player.dirY = 1;
	}
	else if (mprm->player.dir == 'S')
	{
		mprm->player.dirX = 0;
		mprm->player.dirY = -1;
	}
	else if (mprm->player.dir == 'E')
	{
		mprm->player.dirX = 1;
		mprm->player.dirY = 0;
	}
	else if (mprm->player.dir == 'W')
	{
		mprm->player.dirX = -1;
		mprm->player.dirY = 0;
	}
}
