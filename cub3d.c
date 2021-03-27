/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 18:28:34 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/03/26 23:56:18 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_map(int *fd, t_mprm *mprm, t_list **tmp)
{
	int		fl;
	char	*str;

	fl = 0;
	while (get_next_line(*fd, &str))
		if (prs_map_rout(mprm, &str, &fl, tmp) == -1 || fl == 10 || fl == 2)
			return (-1);
	if (prs_map_rout(mprm, &str, &fl, tmp) == -1 || fl == 10 || fl == 2)
		return (-1);
	mprm->map.d += 2;
	mprm->map.w += 2;
	fl = 0;
	if (mprm->ok && !(mprm->map.mp = ft_calloc(mprm->map.d + 1, sizeof(char*))))
		return (red_flag(-1, mprm));
	while (fl <= mprm->map.d)
	{
		if (!(mprm->map.mp[fl] = ft_calloc(mprm->map.w + 1, sizeof(char))))
			return (red_flag(-1, mprm));
		fl++;
	}
	mprm->map.mp[fl] = NULL;
	return (1);
}

int 	map_quest(int *fd, t_mprm *mprm)
{
	char	*str;
	t_list	*tmp_map;

	tmp_map = NULL;
	while (mprm->ok && chk_map_conf(mprm) != 8
		   && get_next_line(*fd, &str) == 1 && prs_rout(mprm, str) != -1)
	{
		free(str);
		str = NULL;
	}
	if (mprm->ok
	&& get_map(fd, mprm, &tmp_map) > 0
	&& make_map(mprm, &tmp_map) > 0
	&& valid_map(mprm) > 0
	)
		return (1);
	free(str);
	str = NULL;
	return (red_flag(-1, mprm));
}

int	main(int argc, char **argv)
{
	int			fd;
	t_mprm		mprm;

	if (argc == 1)
	{
		argc = 2;
		argv[1] = "/home/dmikhaylov/CLionProjects/cub3d/maps/map_2.cub";
	}

	if (argc == 2 || argc == 3)
	{
		cub_init(&mprm);
		if ((fd = open(argv[1], O_RDONLY)) >= 0)
			map_quest(&fd, &mprm);
	}
	else
	{
		write(1, NO_MAP_ERROR, sizeof(NO_MAP_ERROR));
	}
	free_params(&mprm);
	return (0);
}