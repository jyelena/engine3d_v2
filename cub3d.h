/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 21:17:20 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/03/27 21:20:54 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_CUB3D_H
# define CUB_CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

# define NO_MAP_ERROR "Need mp file as argument!\n"

typedef struct		s_map
{
	int				w;
	int				d;
	char			**mp;
}					t_map;

typedef struct		s_chkprm
{
	int				r;
	int				f;
	int				c;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				sp;
}					t_chkprm;

typedef struct		s_resolution {
	int				x;
	int				y;
}					t_resolution;

typedef struct		s_fcolor {
	int				r;
	int				g;
	int				b;
}					t_fcolor;

typedef struct		s_ccolor {
	int				r;
	int				g;
	int				b;
}					t_ccolor;

typedef struct		s_colors {
	t_fcolor		floor_color;
	t_ccolor		cell_color;
}					t_colors;

typedef struct		s_paths {
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sp;
}					t_paths;

typedef struct		s_mprms {
	t_resolution	resolution;
	t_colors		colors;
	t_paths			paths;
	t_chkprm		chk;
	t_map			map;
	int				ok;
}					t_mprm;

void				cub_init(t_mprm *mprm);
void				free_params(t_mprm *mprm);
void				free_list(t_list **list);
void				line_cpy(char *source, char **dest, t_mprm *mprm);
void				free_map_matrix(t_mprm *mprm);
int					free_all(int result, t_mprm *mprm, t_list **list,
					char **str);
int					make_map(t_mprm *mprm, t_list **tmp);
int					red_flag(int result, t_mprm *mprm);
int					valid_map(t_mprm *mprm);
int					chk_in_set(char c, int *flg);
int					trim_space(char **str);
int					trim_space_end(char **str);
int					prs_rout(t_mprm *mprm, char *str);
int					prs_map_rout(t_mprm *mprm, char **str, int *flg,
					t_list **tmp);
int					parse_resolut(t_mprm *mprm, char **str);
int					parse_clr(t_mprm *mprm, char **str, char mode, int *fl);
int					parse_pth(t_mprm *mprm, char **str, char mode, int len);
int					fill_num(char **str, int size);
int					get_chk(t_mprm *mprm, char mode);
int					chk_map_conf(t_mprm	*mprm);

#endif
