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
# include "dymlx/mlx1.h"

# define NO_MAP_ERROR "Error\nNeed map file as argument!"
# define W game->resolution.x
# define H game->resolution.y
# define MAP game.map.mp
# define PMAP game->map.mp
# define texWidth 64
# define texHeight 64
# define MULTSTRAFE 0.3

typedef struct		s_sprt
{
	double			sprt_x;
	double			sprt_y;
	int				sprt_scr_x;
	int				sprt_h;
	int				sprt_w;
	double			inv_det;
	double			trform_x;
	double			trform_y;
	int				drw_start_x;
	int				drw_start_y;
	int				drw_end_x;
	int				drw_end_y;
	int				tex_x;
	int				tex_y;
	int				strp;
	int				y;
	int				d;
	unsigned int	*color;
}					t_sprt;

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
	double 			pos_x;
	double 			pos_y;
	double 			dir_x;
	double 			dir_y;
	double 			plane_x;
	double 			plane_y;
	char 			dir;
}					t_plr;

typedef struct		s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	unsigned int 	*color;
	int				hit;
	int				side;
	int				line_h;
	int				draw_start;
	int				draw_end;
	int				tex_num;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				tex_y;
	double			frame_time;
	double			move_speed;
	double			rot_speed;
	double			old_dir_x;
	double			old_plane_x;
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
	t_ccolor		ceil_color;
}					t_colors;

typedef struct		s_paths {
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sp;
}					t_paths;

typedef struct	s_fname
{
	int 		fd;
	char 		*name;
}				t_fname;

typedef struct		s_game {
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
}					t_game;

void				cub_init(t_game *game);
void				free_params(t_game *game);
void				free_list(t_list **list);
void				line_cpy(char *source, char **dest, t_game *game);
void				free_map_matrix(t_game *game);
void				wrt_err(char *text);
void				player_dir(t_game *game);
void				player_plane(t_game *game);
void				player_position(int x, int y, t_game *game);
void				fill_sprites_struct(t_game *game);
void				draw_init(t_game *game, int sshot_flg);
void				draw_env(t_game *game, int x);
void				draw_ray_calc(t_game *game, int x);
void				draw_side_hit_calc(t_game *game, int x);
void				draw_until_hit(t_game *game, int x);
void				draw_calc_per_ray(t_game *game, int x);
void				draw_calc_wall(t_game *game, int x);
void				draw_coord_calc(t_game *game, int x);
void				draw_lohi_pix_calc(t_game *game, int x);
void				draw_sprites(t_game *game, double **z_buffer, int s);
void				draw_magic(t_game *game, int sshot_flg, int x);
void				get_color(t_game *game);
void				draw_f_c(t_game *game);
void				take_textures(t_game *game);
void				take_tex_addr(t_game *game);
void				my_mlx_pixel_put(t_game *game, int x, int y, int color);
void				strafe_left(t_game *game, double speed);
void				strafe_right(t_game *game, double speed);
void				live_game(t_game *game);
void				process_option(char *option, t_game *game);
void				file_init(t_fname *file);
void				take_screenshot(t_game *game, t_fname *file);
void				get_screen_size(t_game *game, int sshot_flg);
int					close_win(void);
int					create_rgb(int r, int g, int b);
int					key_press(int key, t_game *game);
int					key_release(int key, t_game *game);
int					moving(t_game *game);
int					free_all(int result, t_game *game, t_list **list);
int					make_map(t_game *game, t_list **tmp);
int					red_flag(int result, t_game *game);
int					valid_map(t_game *game);
int					chk_in_set(char c, int *flg);
int					trim_space(char **str);
int					trim_space_end(char **str);
int					prs_rout(t_game *game, char *str);
int					prs_map_rout(t_game *game, char **str, int *flg,
									t_list **tmp);
int					parse_resolut(t_game *game, char **str);
int					parse_clr(t_game *game, char **str, char mode, int *fl);
int					parse_pth(t_game *game, char **str, char mode, int len);
int					fill_num(char **str, int size);
int					get_chk(t_game *game, char mode);
int					chk_map_conf(t_game	*game);
unsigned int		*take_pixel(t_tex tex, int x, int y);

#endif
