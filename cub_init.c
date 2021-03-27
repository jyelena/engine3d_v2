/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:30:57 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/03/24 17:23:44 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_init(t_mprm *mprm)
{
	mprm->ok = 1;
	mprm->map.w = 0;
	mprm->map.d = 0;
	mprm->chk.r = 0;
	mprm->chk.f = 0;
	mprm->chk.c = 0;
	mprm->chk.no = 0;
	mprm->chk.so = 0;
	mprm->chk.we = 0;
	mprm->chk.ea = 0;
	mprm->chk.sp = 0;
	mprm->resolution.x = -1;
	mprm->resolution.y = -1;
	mprm->colors.cell_color.r = -1;
	mprm->colors.cell_color.g = -1;
	mprm->colors.cell_color.b = -1;
	mprm->colors.floor_color.r = -1;
	mprm->colors.floor_color.g = -1;
	mprm->colors.floor_color.b = -1;
}