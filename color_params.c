#include "cub3d.h"

int				create_rgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

void 			get_color(t_mprm *mprm)
{
	mprm->colors.cell_color.rgb = create_rgb(mprm->colors.cell_color.r,
										  mprm->colors.cell_color.g,
										  mprm->colors.cell_color.b);
	mprm->colors.floor_color.rgb = create_rgb(mprm->colors.floor_color.r,
										  mprm->colors.floor_color.g,
										  mprm->colors.floor_color.b);
}

unsigned int	*take_pixel(t_tex tex, int x, int y)
{
	return ((unsigned int *)(tex.timg.addr + (y * tex.timg.linelen + x * (tex
	.timg.bpp / 8))));
}

void			take_textures(t_mprm *mprm)
{
	mprm->tex.no.timg.img = mlx_xpm_file_to_image(mprm->data.mlx,
	mprm->paths.no, &(mprm->tex.no.w), &(mprm->tex.no.h));
	mprm->tex.so.timg.img = mlx_xpm_file_to_image(mprm->data.mlx,
	mprm->paths.so, &(mprm->tex.so.w), &(mprm->tex.so.h));
	mprm->tex.ea.timg.img = mlx_xpm_file_to_image(mprm->data.mlx,
	mprm->paths.ea, &(mprm->tex.ea.w), &(mprm->tex.ea.h));
	mprm->tex.we.timg.img = mlx_xpm_file_to_image(mprm->data.mlx,
	mprm->paths.we, &(mprm->tex.we.w), &(mprm->tex.we.h));
	mprm->tex.sp.timg.img = mlx_xpm_file_to_image(mprm->data.mlx,
	mprm->paths.sp, &(mprm->tex.sp.w), &(mprm->tex.sp.h));
}

void			take_tex_addr(t_mprm *mprm)
{
	mprm->tex.no.timg.addr = mlx_get_data_addr(mprm->tex.no.timg.img,
	&(mprm->tex.no.timg.bpp), &(mprm->tex.no.timg.linelen),
	&(mprm->tex.no.timg.endian));
	mprm->tex.so.timg.addr = mlx_get_data_addr(mprm->tex.so.timg.img,
	&(mprm->tex.so.timg.bpp), &(mprm->tex.so.timg.linelen),
	&(mprm->tex.so.timg.endian));
	mprm->tex.ea.timg.addr = mlx_get_data_addr(mprm->tex.ea.timg.img,
	&(mprm->tex.ea.timg.bpp), &(mprm->tex.ea.timg.linelen),
	&(mprm->tex.ea.timg.endian));
	mprm->tex.we.timg.addr = mlx_get_data_addr(mprm->tex.we.timg.img,
	&(mprm->tex.we.timg.bpp), &(mprm->tex.we.timg.linelen),
	&(mprm->tex.we.timg.endian));
	mprm->tex.sp.timg.addr = mlx_get_data_addr(mprm->tex.sp.timg.img,
	&(mprm->tex.sp.timg.bpp), &(mprm->tex.sp.timg.linelen),
	&(mprm->tex.sp.timg.endian));
}
