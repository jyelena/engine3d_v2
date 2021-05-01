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

void	free_map_matrix(t_game *game)
{
	int i;

	i = 0;
	while (i < game->map.d)
	{
		if (game->map.mp[i])
			free(game->map.mp[i]);
		i++;
	}
	if (game->map.mp)
		free(game->map.mp);
}

void	free_all(t_game *game, t_list **list)
{
	if (list && *list)
		free_list(list);
	if (game->map.mp && *(game->map.mp))
		free_map_matrix(game);
	exit(0);
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

void	free_params(t_game *game)
{
	if (game->chk.no == 1)
		free(game->paths.no);
	if (game->chk.so == 1)
		free(game->paths.so);
	if (game->chk.we == 1)
		free(game->paths.we);
	if (game->chk.ea == 1)
		free(game->paths.ea);
	if (game->chk.sp == 1)
		free(game->paths.sp);
}
