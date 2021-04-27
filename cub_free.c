/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:24:59 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/04/02 03:33:43 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		red_flag(int result, t_mprm *mprm)
{
	if (result < 0)
	{
		mprm->ok = 0;
		if (result == -1)
			wrt_err("Invalid params");
		if (result == -3)
			wrt_err("Map not found");
		else if (result == -12)
			wrt_err("Invalid resolution");
		else if (result == -2)
			wrt_err("Invalid map");
		else if (result == -11)
			wrt_err("Invalid color params");
		else if (result == -13)
			wrt_err("Invalid filename");
		else
			wrt_err("Error");
	}
	return (result);
}

void	free_map_matrix(t_mprm *mprm)
{
	int i;

	i = 0;
	while (i < mprm->map.d)
	{
		if (mprm->map.mp[i])
			free(mprm->map.mp[i]);
		i++;
	}
	if (mprm->map.mp)
		free(mprm->map.mp);
}

int		free_all(int result, t_mprm *mprm, t_list **list)
{
	red_flag(result, mprm);
	if (list && *list)
		free_list(list);
	if (mprm->map.mp && *(mprm->map.mp))
		free_map_matrix(mprm);
	if (result < 0)
		mprm->ok = 0;
	return (result);
}

void	free_list(t_list **list)
{
	t_list *current;
	t_list *tempor;

	if (list && *list)
	{
		current = *list;
		while (current->next)
		{
			tempor = current->next;
			if (current->content)
			{
				free(current->content);
				current->content = NULL;
			}
			free(current);
			current = tempor;
		}
		if (current->content)
		{
			free(current->content);
			current->content = NULL;
		}
		free(current);
	}
}

void	free_params(t_mprm *mprm)
{
	if (mprm->chk.no == 1)
		free(mprm->paths.no);
	if (mprm->chk.so == 1)
		free(mprm->paths.so);
	if (mprm->chk.we == 1)
		free(mprm->paths.we);
	if (mprm->chk.ea == 1)
		free(mprm->paths.ea);
	if (mprm->chk.sp == 1)
		free(mprm->paths.sp);
}
