/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 18:28:34 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/04/02 03:30:05 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_filename_valid(char *f_name)
{
	int		len;

	len = ft_strlen(f_name);
	if (f_name[len - 1] != 'b' || f_name[len - 2] != 'u'
	|| f_name[len - 3] != 'c' || f_name[len - 4] != '.')
	{
		wrt_err("Error in map filename");
		exit(0);
	}
}

int		get_map(int *fd, t_game *game, t_list **tmp)
{
	int		fl;
	char	*str;

	fl = 0;
	while (get_next_line(*fd, &str))
		if (prs_map_rout(game, &str, &fl, tmp) < 0 || fl == 10 || fl == 2)
			return (free_all(-2, game, tmp));
	if (prs_map_rout(game, &str, &fl, tmp) < 0 || fl == 10 || fl == 1
	|| fl == 0)
		return (free_all(-2, game, tmp));
	game->map.d += 2;
	game->map.w += 2;
	fl = 0;
	if (game->ok && !(game->map.mp = ft_calloc(game->map.d + 1, sizeof(char*))))
		return (free_all(-2, game, tmp));
	while (fl < game->map.d)
	{
		if (!(game->map.mp[fl] = ft_calloc(game->map.w + 1, sizeof(char))))
			return (free_all(-1, game, tmp));
		fl++;
	}
	game->map.mp[fl] = NULL;
	return (1);
}

int		map_quest(int *fd, t_game *game)
{
	char	*str;
	t_list	*tmp_map;

	tmp_map = NULL;
	str = NULL;
	while (game->ok && chk_map_conf(game) != 8
	&& get_next_line(*fd, &str) == 1
	&& prs_rout(game, str) > -1)
	{
		free(str);
		str = NULL;
	}
	if (game->ok
	&& get_map(fd, game, &tmp_map) > 0
	&& make_map(game, &tmp_map) > 0
	&& valid_map(game) > 0)
	{
		get_color(game);
		return (1);
	}
	free(str);
	str = NULL;
	return (-1);
}

int		main(int argc, char **argv)
{
	int			fd;
	t_game		game;

	if (argc == 2 || argc == 3)
	{
		map_filename_valid(argv[1]);
		cub_init(&game);
		if ((fd = open(argv[1], O_RDONLY)) >= 0)
		{
			if (map_quest(&fd, &game) > 0)
			{
				draw_init(&game);
			}
		}
	}
	else
		wrt_err(NO_MAP_ERROR);
	free_params(&game);
	if (game.map.mp && *(game.map.mp))
		free_map_matrix(&game);
	return (0);
}
