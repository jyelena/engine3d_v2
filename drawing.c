#include "cub3d.h"

void            my_mlx_pixel_put(t_mprm *mprm, int x, int y, int color)
{
	char    *dst;

	dst = mprm->data.addr + (y * mprm->data.line_length + x * (mprm->data
			.bits_per_pixel
			/ 8));
	*(unsigned int*)dst = color;
}

void 	draw_f_c(t_mprm *mprm)
{
	int x;
	int y;

	y = 0;
	while (y <= H / 2)
	{
		x = 0;
		while(x < W)
			my_mlx_pixel_put(mprm, x++, y, mprm->colors.cell_color.rgb);
		y++;
	}
	while (y < H)
	{
		x = 0;
		while(x < W)
			my_mlx_pixel_put(mprm, x++, y, mprm->colors.floor_color.rgb);
		y++;
	}

}

void		draw_magic(t_mprm *mprm)
{
	int x;

	x = -1;
	draw_f_c(mprm);
	while (++x < W)
	{
		mprm->ray.cameraX = 2 * x / (double)W - 1;
		mprm->ray.rayDirX = mprm->plr.dirX + mprm->plr.planeX
				* mprm->ray.cameraX;
		mprm->ray.rayDirY = mprm->plr.dirY + mprm->plr.planeY
				* mprm->ray.cameraX;
		//which box of the map we're in
		mprm->ray.mapX = (int)mprm->plr.posX;
		mprm->ray.mapY = (int)mprm->plr.posY;
//		printf("x: %f, y: %f\n", mprm->plr.posX, mprm->plr.posY);

		//length of ray from one x or y-side to next x or y-side
		if (mprm->ray.rayDirY == 0)
			mprm->ray.deltaDistX = 0;
		else
		{
			if (mprm->ray.rayDirX == 0)
				mprm->ray.deltaDistX = 1;
			else
				mprm->ray.deltaDistX = fabs(1 / mprm->ray.rayDirX);
		}
		if (mprm->ray.rayDirX == 0)
			mprm->ray.deltaDistY = 0;
		else
		{
			if (mprm->ray.rayDirY == 0)
				mprm->ray.deltaDistY = 1;
			else
				mprm->ray.deltaDistY = fabs(1 / mprm->ray.rayDirY);
		}
		mprm->ray.hit = 0; //was there a wall hit?
		mprm->ray.sideDistX = 0;
		if(mprm->ray.rayDirX < 0)
		{
			mprm->ray.stepX = -1;
			mprm->ray.sideDistX = (mprm->plr.posX - mprm->ray.mapX)
					* mprm->ray.deltaDistX;
		}
		else
		{
			mprm->ray.stepX = 1;
			mprm->ray.sideDistX = (mprm->ray.mapX + 1.0 - mprm->plr.posX)
					* mprm->ray.deltaDistX;
		}
		if(mprm->ray.rayDirY < 0)
		{
			mprm->ray.stepY = -1;
			mprm->ray.sideDistY = (mprm->plr.posY - mprm->ray.mapY)
					* mprm->ray.deltaDistY;
		}
		else
		{
			mprm->ray.stepY = 1;
			mprm->ray.sideDistY = (mprm->ray.mapY + 1.0 - mprm->plr.posY)
					* mprm->ray.deltaDistY;
		}
		while (mprm->ray.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (mprm->ray.sideDistX < mprm->ray.sideDistY)
			{
				mprm->ray.sideDistX += mprm->ray.deltaDistX;
				mprm->ray.mapX += mprm->ray.stepX;
				mprm->ray.side = 0;
			}
			else
			{

				mprm->ray.sideDistY += mprm->ray.deltaDistY;
				mprm->ray.mapY += mprm->ray.stepY;
				mprm->ray.side = 1;
			}
			//Check if ray has hit a wall
			if (PMAP[mprm->ray.mapY][mprm->ray.mapX] == '1')
				mprm->ray.hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if (mprm->ray.side == 0)
		{
			mprm->ray.perpWallDist = (mprm->ray.mapX - mprm->plr.posX
					+ (1.0 - mprm->ray.stepX) / 2) / mprm->ray.rayDirX;
		}
		else
		{
			mprm->ray.perpWallDist = (mprm->ray.mapY - mprm->plr.posY
					+ (1.0 - mprm->ray.stepY) / 2) / mprm->ray.rayDirY;
		}
		//Calculate height of line to draw on screen
		mprm->ray.lineHeight = (int)(H / mprm->ray.perpWallDist);
		//calculate lowest and highest pixel to fill in current stripe
		mprm->ray.drawStart = -mprm->ray.lineHeight / 2 + H / 2;
		if(mprm->ray.drawStart < 0)
			mprm->ray.drawStart = 0;
		mprm->ray.drawEnd = mprm->ray.lineHeight / 2 + H / 2;
		if(mprm->ray.drawEnd >= H)
			mprm->ray.drawEnd = H;
		//texturing calculations
		mprm->ray.texNum = PMAP[mprm->ray.mapY][mprm->ray.mapX] - 1; //1
		// subtracted
		// from it so that texture 0 can be used!

		//calculate value of wallX
		if(mprm->ray.side == 0)
			mprm->ray.wallX = mprm->plr.posY
					+ mprm->ray.perpWallDist * mprm->ray.rayDirY;
		else
			mprm->ray.wallX = mprm->plr.posX + mprm->ray.perpWallDist
					* mprm->ray.rayDirX;
		mprm->ray.wallX -= floor((mprm->ray.wallX));

		//x coordinate on the texture
		mprm->ray.texX = (int)(mprm->ray.wallX * (double)texWidth);
		if(mprm->ray.side == 0 && mprm->ray.rayDirX > 0) mprm->ray.texX =
				texWidth - mprm->ray.texX - 1;
		if(mprm->ray.side == 1 && mprm->ray.rayDirY < 0) mprm->ray.texX =
				texWidth - mprm->ray.texX - 1;

		// How much to increase the texture coordinate per screen pixel
		mprm->ray.step = 1.0 * texHeight / mprm->ray.lineHeight;
		// Starting texture coordinate
		mprm->ray.texPos = (mprm->ray.drawStart - H / 2.0
				+ mprm->ray.lineHeight / 2.0) * mprm->ray.step;
		t_tex ptex;
		int y = mprm->ray.drawStart;
		while ( y < mprm->ray.drawEnd)
		{
//			printf("side  = %d stepx = %d\n", mprm->ray.side, mprm->ray.stepX);
			if (mprm->ray.side == 0 && mprm->ray.stepX > 0)
				ptex = mprm->tex.ea;
			else if (mprm->ray.side == 0 && mprm->ray.stepX < 0)
				ptex = mprm->tex.we;
			else if (mprm->ray.side == 1 && mprm->ray.stepY > 0)
				ptex = mprm->tex.so;
			else
				ptex = mprm->tex.no;
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			mprm->ray.texY = (int)mprm->ray.texPos & (texHeight - 1);
			mprm->ray.texPos += mprm->ray.step;
			mprm->ray.color = take_pixel(ptex, mprm->ray.texX, mprm->ray.texY);
			my_mlx_pixel_put(mprm, x, y, (int)(*mprm->ray.color));
			y++;
		}
	}

	mlx_put_image_to_window(mprm->data.mlx, mprm->data.win, mprm->data.img,
						 0, 0);
	mlx_destroy_image(mprm->data.mlx, mprm->data.img);
	mprm->data.img = mlx_new_image(mprm->data.mlx, W, H);
	mprm->data.addr = mlx_get_data_addr(mprm->data.img, &mprm->data
	.bits_per_pixel, &mprm->data.line_length, &mprm->data.endian);
}

void		draw_init(t_mprm *mprm)
{

	mprm->data.mlx = mlx_init();
	mprm->data.win = mlx_new_window(mprm->data.mlx, W, H, "");
	mprm->data.img = mlx_new_image(mprm->data.mlx, W, H);
	mprm->data.addr = mlx_get_data_addr(mprm->data.img, &mprm->data
	.bits_per_pixel, &mprm->data.line_length, &mprm->data.endian);
	take_textures(mprm);
	take_tex_addr(mprm);
	draw_magic(mprm);
	mlx_hook(mprm->data.win, 2, (1L << 0), &key_press, mprm);
	mlx_hook(mprm->data.win, 3, (1L << 1), &key_release, mprm);
	mlx_loop_hook(mprm->data.mlx, &moving, mprm);
	mlx_loop(mprm->data.mlx);
}