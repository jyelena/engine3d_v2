/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmikhaylov <dmikhaylov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 21:17:20 by dmikhaylov        #+#    #+#             */
/*   Updated: 2021/04/26 20:31:19 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "mlx/mlx.h"

# define NO_MAP_ERROR "Need map file as argument!\n"
# define W mprm->resolution.x
# define H mprm->resolution.y

# define MAP mprm.map.mp
# define PMAP mprm->map.mp
# define texWidth 64
# define texHeight 64

typedef struct		s_move
{
	short			up;
	short			down;
	short			turn_left;
	short			turn_right;
	short			strafe_left;
	short			strafe_right;
	short			exit;
}					t_move;

typedef struct		s_img
{
	void			*img;
	void			*addr;
	int				bpp;
	int				linelen;
	int				endian;
}					t_img;

typedef struct		s_tex
{
	t_img			timg;
	int				w;
	int				h;
}					t_tex;

typedef struct		s_alltex
{
	t_tex			no;
	t_tex			so;
	t_tex			ea;
	t_tex			we;
	t_tex			sp;
}					t_alltex;

typedef struct		s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	void			*mlx;
	void			*win;
}					t_data;

typedef struct		s_spr
{
	double			x;
	double			y;
	double			dist;
}					t_spr;

typedef struct 		s_plr
{
	double 			posX;
	double 			posY;
	double 			dirX;
	double 			dirY;
	double 			planeX;
	double 			planeY;
	char 			dir;
}					t_plr;

typedef struct		s_ray
{
	double			cameraX;
	double			rayDirX;
	double			rayDirY;
	int				mapX;
	int				mapY;
	double			sideDistX;
	double			sideDistY;
	double			deltaDistX;
	double			deltaDistY;
	double			perpWallDist;
	int				stepX;
	int				stepY;
	unsigned int 	*color;
	int				hit;
	int				side;
	int				lineHeight;
	int				drawStart;
	int				drawEnd;
	int				texNum;
	double			wallX;
	int				texX;
	double			step;
	double			texPos;
	int				texY;
	double			frameTime;
	double			moveSpeed;
	double			rotSpeed;
	double			oldDirX;
	double			oldPlaneX;
}					t_ray;

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
	unsigned int 	rgb;
}					t_fcolor;

typedef struct		s_ccolor {
	int				r;
	int				g;
	int				b;
	unsigned int 	rgb;
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
	t_plr			plr;
	t_spr			*spr;
	t_ray			ray;
	t_data			data;
	t_move			mov;
	t_alltex		tex;
	int 			scount;
	int				ok;
}					t_mprm;

void				cub_init(t_mprm *mprm);
void				free_params(t_mprm *mprm);
void				free_list(t_list **list);
void				line_cpy(char *source, char **dest, t_mprm *mprm);
void				free_map_matrix(t_mprm *mprm);
void				wrt_err(char *text);
void				player_dir(t_mprm *mprm);
void				player_plane(t_mprm *mprm);
void				player_position(int x, int y, t_mprm *mprm);
void				fill_sprites_struct(t_mprm *mprm);
void				draw_init(t_mprm *mprm);
void				draw_magic(t_mprm *mprm);
void				get_color(t_mprm *mprm);
void				draw_f_c(t_mprm *mprm);
void				take_textures(t_mprm *mprm);
void				take_tex_addr(t_mprm *mprm);
int					create_rgb(int r, int g, int b);
int					key_press(int key, t_mprm *mprm);
int					key_release(int key, t_mprm *mprm);
int					moving(t_mprm *mprm);
int					free_all(int result, t_mprm *mprm, t_list **list);
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
unsigned int		*take_pixel(t_tex tex, int x, int y);

#endif
