/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 18:28:34 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/04/30 15:29:44 by jyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		map_filename_valid(char *f_name, int argc)
{
	int		len;

	len = ft_strlen(f_name);
	if (f_name[len - 1] != 'b' || f_name[len - 2] != 'u'
			|| f_name[len - 3] != 'c' || f_name[len - 4] != '.')
		wrt_err("Invalid map filename", 1);
	if (argc == 2)
		return (0);
	return (1);
}

int		get_map(int *fd, t_game *game, t_list **tmp)
{
	int		fl;
	char	*str;

	fl = -1;
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
	if (read(*fd, str, 0) < 0)
		wrt_err("Invalid config file", 1);
	while (game->ok && chk_map_conf(game) != 8
	&& get_next_line(*fd, &str) == 1 && prs_rout(game, str) > -1)
	{
		free(str);
		str = NULL;
	}
	if (game->ok && get_map(fd, game, &tmp_map) > 0
	&& make_map(game, &tmp_map) > 0 && valid_map(game) > 0)
	{
		get_color(game);
		return (1);
	}
	free(str);
	str = NULL;
	return (-1);
}

void	process_option(char *option, t_game *game)
{
	t_fname	file;

	if (ft_strlen(option) != ft_strlen("--save") ||
	ft_strncmp(option, "--save", ft_strlen(option)) != 0)
		wrt_err("Unknown option", 1);
	file_init(&file);
	take_screenshot(game, &file);
	exit(0);
}

int		main(int argc, char **argv)
{
	int			fd;
	int			sshot_flg;
	t_game		game;

	if (argc == 2 || argc == 3)
	{
		sshot_flg = map_filename_valid(argv[1], argc);
		cub_init(&game);
		if ((fd = open(argv[1], O_RDONLY)) >= 0)
		{
			if (map_quest(&fd, &game) > 0)
			{
				draw_init(&game, sshot_flg);
				if (argc == 3)
					process_option(argv[2], &game);
				live_game(&game);
			}
		}
	}
	else
		wrt_err(NO_MAP_ERROR, 1);
	free_params(&game);
	if (game.map.mp && *(game.map.mp))
		free_map_matrix(&game);
	return (0);
}
