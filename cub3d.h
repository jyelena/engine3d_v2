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

# define NO_MAP_ERROR "Need map file as argument!\n"
# define W mprm->resolution.x
# define H mprm->resolution.y

# define MAP mprm.map.mp
# define PMAP mprm->map.mp
# define screenWidth 640
# define screenHeight 480
# define texWidth 64
# define texHeight 64
# define mapWidth 24
# define mapHeight 24

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

typedef struct 		s_player
{
	double 			x;
	double 			y;
	double 			dirX;
	double 			dirY;
	double 			planeX;
	double 			planeY;
	char 			dir;
}					t_player;

typedef struct		s_ray
{
	double			cameraX; // = 2 * x / (double)w - 1; //x-coordinate in camera space
	double			rayDirX; // = dirX + planeX*cameraX;
	double			rayDirY; // = dirY + planeY*cameraX;
	int				mapX; // = int(posX);
	int				mapY; // = int(posY);
	double			sideDistX;
	double			sideDistY;
	double			deltaDistX; // = std::abs(1 / rayDirX);
	double			deltaDistY; // = std::abs(1 / rayDirY);
	double			perpWallDist;
	int				stepX;
	int				stepY;
	int				color;
	int				hit; // = 0; //was there a wall hit?
	int				side; //was a NS or a EW wall hit?
	int				lineHeight; // = (int)(h / perpWallDist);
	int				drawStart; // = -lineHeight / 2 + h / 2;
	int				drawEnd; // = lineHeight / 2 + h / 2;
	int				texNum; // = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!
	double			wallX; // where exactly the wall was hit
	int				texX; // = int(wallX * double(texWidth));
	double			step; // = 1.0 * texHeight / lineHeight;
	double			texPos; // = (drawStart - h / 2 + lineHeight / 2) * step;
	int				texY; // = (int)texPos & (texHeight - 1);
	double			frameTime; //= (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
	double			moveSpeed; // = frameTime * 5.0; //the constant value is in squares/second
	double			rotSpeed; // = frameTime * 3.0; //the constant value is in radians/second
	double			oldDirX; // = dirX;
	double			oldPlaneX; // = planeX;
}					t_ray;

typedef struct		s_map
{
	int				w;
	int				d;
	int 			spr_sum;
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
	t_player		player;
	t_spr			*spr;
	t_ray			ray;
	int				ok;
}					t_mprm;

void				cub_init(t_mprm *mprm);
void				free_params(t_mprm *mprm);
void				free_list(t_list **list);
void				line_cpy(char *source, char **dest, t_mprm *mprm);
void				free_map_matrix(t_mprm *mprm);
void				wrt_err(char *text);
void				player_dir(t_mprm *mprm);
void				fill_sprites_struct(char **map, t_spr **spr_arr);
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

#endif
