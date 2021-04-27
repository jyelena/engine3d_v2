#include "cub3d.h"

void            my_mlx_pixel_put(t_mprm *mprm, int x, int y, int color)
{
	char    *dst;

	dst = mprm->data.addr + (y * mprm->data.line_length + x * (mprm->data
			.bits_per_pixel
			/ 8));
	*(unsigned int*)dst = color;
}

void             key_hook(int keycode, t_data *vars)
{
	printf("Hello from key_hook!\n");
}

int		key_press(int key, t_mprm *mprm)
{
	if(key == 111)
	{
		if(mprm->map.mp[(int)(mprm->plr.posX + mprm->plr.dirX
		* 0.5)][(int)(mprm->plr.posY)] != '1')
			mprm->plr.posX += mprm->plr.dirX * 0.5;
		if(mprm->map.mp[(int)(mprm->plr.posX)][(int)(mprm->plr.posY
		+ mprm->plr.dirY * 0.5)] != '1')
			mprm->plr.posY += mprm->plr.dirY * 0.5;
		write(1, "test\n", 5);
	}
	//move backwards if no wall behind you
	if(key == 116)
	{
		if(mprm->map.mp[(int)(mprm->plr.posX - mprm->plr.dirX
		* 0.5)][(int)(mprm->plr.posY)] != '1')
			mprm->plr.posX -= mprm->plr.dirX * 0.5;
		if(mprm->map.mp[(int)(mprm->plr.posX)][(int)(mprm->plr.posY
		- mprm->plr.dirY * 0.5)] != '1')
			mprm->plr.posY -= mprm->plr.dirY * 0.5;
		write(1, "test2\n", 6);
	}
	draw_magic(mprm);
	return (0);
	//rotate to the right
}

void		draw_magic(t_mprm *mprm)
{
	int x = -1;
	while (++x < W)
	{
		mprm->ray.cameraX = 2 * x / (double)W - 1; //x-coordinate in camera
		// space
		mprm->ray.rayDirX = mprm->plr.dirX + mprm->plr.planeX * mprm->ray
				.cameraX;
		mprm->ray.rayDirY = mprm->plr.dirY + mprm->plr.planeY * mprm->ray
				.cameraX;

		//which box of the map we're in
		mprm->ray.mapX = (int)mprm->plr.posX;
		mprm->ray.mapY = (int)mprm->plr.posY;

		//length of ray from one x or y-side to next x or y-side
//		mprm->ray.deltaDistX = (mprm->ray.rayDirY == 0) ? 0 : ((mprm->ray.rayDirX == 0) ? 1 : fabs(1 / mprm->ray.rayDirX));
//		mprm->ray.deltaDistX = (mprm->ray.rayDirX == 0) ? 0 : ((mprm->ray.rayDirY == 0) ? 1 : fabs(1 / mprm->ray.rayDirY));
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
			mprm->ray.deltaDistX = 0;
		else
		{
			if (mprm->ray.rayDirY == 0)
				mprm->ray.deltaDistX = 1;
			else
				mprm->ray.deltaDistX = fabs(1 / mprm->ray.rayDirY);
		}
		mprm->ray.hit = 0; //was there a wall hit?
		mprm->ray.sideDistX = 0;
		if(mprm->ray.rayDirX < 0)
		{
			mprm->ray.stepX = -1;
			mprm->ray.sideDistX = (mprm->plr.posX - mprm->ray.mapX) *
					mprm->ray.deltaDistX;
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
			mprm->ray.sideDistY = (mprm->plr.posY - mprm->ray.mapY) *
					mprm->ray.deltaDistY;
		}
		else
		{
			mprm->ray.stepY = 1;
			mprm->ray.sideDistY = (mprm->ray.mapY + 1.0 - mprm->plr.posY) *
					mprm->ray.deltaDistY;
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
			{
				mprm->ray.hit = 1;
			}
		}
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if (mprm->ray.side == 0)
		{

			mprm->ray.perpWallDist = (mprm->ray.mapX - mprm->plr.posX +
					(1.0 - mprm->ray.stepX) / 2) / mprm->ray.rayDirX;
//			printf("mapX - %d, posX - %f, dirX - %f, perpWallDist - %f\n",
//			mprm->ray.mapX, mprm->plr.posX, mprm->ray.rayDirX, mprm->ray
//			.perpWallDist);
		}
		else
		{

			mprm->ray.perpWallDist = (mprm->ray.mapY - mprm->plr.posY +
					(1.0 - mprm->ray.stepY) / 2) / mprm->ray.rayDirY;
//			printf("mapY - %d, posY - %f, dirY - %f, perpWallDist - %f\n",
//			mprm->ray.mapY, mprm->plr.posY, mprm->ray.rayDirY, mprm->ray
//			.perpWallDist);
		}
		//Calculate height of line to draw on screen
		mprm->ray.lineHeight = (int)(H / mprm->ray.perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		mprm->ray.drawStart = -mprm->ray.lineHeight / 2 + H / 2;
		if(mprm->ray.drawStart < 0)
			mprm->ray.drawStart = 0;
		mprm->ray.drawEnd = mprm->ray.lineHeight / 2 + H / 2;
		if(mprm->ray.drawEnd >= H)
			mprm->ray.drawEnd = H - 1;

		//texturing calculations
		mprm->ray.texNum = PMAP[mprm->ray.mapY][mprm->ray.mapX] - 1; //1
		// subtracted
		// from it so that texture 0 can be used!

		//calculate value of wallX
//		mprm->ray.wallX; //where exactly the wall was hit
		if(mprm->ray.side == 0) mprm->ray.wallX = mprm->plr.posY +
				mprm->ray.perpWallDist * mprm->ray.rayDirY;
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

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		mprm->ray.step = 1.0 * texHeight / mprm->ray.lineHeight;
		// Starting texture coordinate
		mprm->ray.texPos = (mprm->ray.drawStart - H / 2.0
				+ mprm->ray.lineHeight / 2.0) * mprm->ray.step;
//		printf("x - %d\n", x);
//		printf("drawStart - %d\n", mprm->ray.drawStart);
//		printf("drawEnd - %d\n", mprm->ray.drawEnd);
		for(int y = mprm->ray.drawStart; y < mprm->ray.drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			mprm->ray.texY = (int)mprm->ray.texPos & (texHeight - 1);
			mprm->ray.texPos += mprm->ray.step;
			if(mprm->ray.side == 1)
				mprm->ray.color = 0xff00ff; // (mprm->ray
			// .color
			// >>
			// 1) & 8355711;
//			printf("x - %d, y - %d\n", x, y);
			my_mlx_pixel_put(mprm, x, y, 0xff0000); // mprm->ray.color);
		}
	}
	mlx_put_image_to_window(mprm->data.mlx, mprm->data.win, mprm->data.img,
						 0, 0);
}

void		draw_init(t_mprm *mprm)
{
	mprm->data.mlx = mlx_init();
	mprm->data.win = mlx_new_window(mprm->data.mlx, W, H, "");
	mprm->data.img = mlx_new_image(mprm->data.mlx, W, H);
	mprm->data.addr = mlx_get_data_addr(mprm->data.img, &mprm->data
	.bits_per_pixel, &mprm->data.line_length, &mprm->data.endian);
//	mlx_put_image_to_window(mprm->data.mlx, mprm->data.win, mprm->data.img, 0,
//	0);

//	x = -1;
	draw_magic(mprm);
//	while (++x < W)
//	{
//		mprm.ray.cameraX = 2 * x / (double)W - 1; //x-coordinate in camera space
//		mprm.ray.rayDirX = mprm->plr.dirX + mprm->plr.planeX*mprm.ray
//		.cameraX;
//		mprm.ray.rayDirY = mprm->plr.dirY + mprm->plr.planeY*mprm.ray
//		.cameraX;
//
//		//which box of the map we're in
//		mprm.ray.mapX = (int)mprm->plr.posX;
//		mprm.ray.mapY = (int)mprm->plr.posY;
//
//		//length of ray from one x or y-side to next x or y-side
//		mprm.ray.deltaDistX = fabs(1 / mprm.ray.rayDirX);
//		mprm.ray.deltaDistY = fabs(1 / mprm.ray.rayDirY);
//
//		mprm.ray.hit = 0; //was there a wall hit?
//		mprm.ray.sideDistX = 0;
//		if(mprm.ray.rayDirX < 0)
//		{
//			mprm.ray.stepX = -1;
//			mprm.ray.sideDistX = (mprm->plr.posX - mprm.ray.mapX) * mprm
//			.ray
//			.deltaDistX;
//		}
//		else
//		{
//			mprm.ray.stepX = 1;
//			mprm.ray.sideDistX = (mprm.ray.mapX + 1.0 - mprm->plr.posX) *
//			mprm
//			.ray
//			.deltaDistX;
//		}
//		if(mprm.ray.rayDirY < 0)
//		{
//			mprm.ray.stepY = -1;
//			mprm.ray.sideDistY = (mprm->plr.posY - mprm.ray.mapY) * mprm
//			.ray
//			.deltaDistY;
//		}
//		else
//		{
//			mprm.ray.stepY = 1;
//			mprm.ray.sideDistY = (mprm.ray.mapY + 1.0 - mprm->plr.posY) *
//			mprm
//			.ray
//			.deltaDistY;
//		}
//		while (mprm.ray.hit == 0)
//		{
//			//jump to next map square, OR in x-direction, OR in y-direction
//			if (mprm.ray.sideDistX < mprm.ray.sideDistY)
//			{
//				mprm.ray.sideDistX += mprm.ray.deltaDistX;
//				mprm.ray.mapX += mprm.ray.stepX;
//				mprm.ray.side = 0;
//			}
//			else
//				{
//				mprm.ray.sideDistY += mprm.ray.deltaDistY;
//				mprm.ray.mapY += mprm.ray.stepY;
//				mprm.ray.side = 1;
//			}
//			//Check if ray has hit a wall
//			if (WORLDPMAP[mprm.ray.mapY][mprm.ray.mapX] == '1') mprm.ray.hit
//			= 1;
//		}
//		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
//		if (mprm.ray.side == 0)
//		{
//			mprm.ray.perpWallDist = (mprm.ray.mapX - mprm->plr.posX + (1
//			.0 -
//			mprm.ray
//			.stepX) / 2) / mprm.ray.rayDirX;
////			printf("mapX - %d, posX - %f, dirX - %f, perpWallDist -
// %f\n", mprm.ray.mapX, mprm->plr.posX, mprm.ray.rayDirX, mprm.ray
// .perpWallDist);
//		}
//		else
//		{
//			mprm.ray.perpWallDist = (mprm.ray.mapY - mprm->plr.posY + (1
//			.0 -
//			mprm.ray
//			.stepY) / 2) / mprm.ray.rayDirY;
////			printf("mapY - %d, posY - %f, dirY - %f, perpWallDist -
// %f\n", mprm.ray.mapY, mprm->plr.posY, mprm.ray.rayDirY, mprm.ray
// .perpWallDist);
//		}
//		//Calculate height of line to draw on screen
//		mprm.ray.lineHeight = (int)(H / mprm.ray.perpWallDist);
//
//		//calculate lowest and highest pixel to fill in current stripe
//		mprm.ray.drawStart = -mprm.ray.lineHeight / 2 + H / 2;
//		if(mprm.ray.drawStart < 0) mprm.ray.drawStart = 0;
//		mprm.ray.drawEnd = mprm.ray.lineHeight / 2 + H / 2;
//		if(mprm.ray.drawEnd >= H) mprm.ray.drawEnd = H - 1;
//
//		//texturing calculations
//		mprm.ray.texNum = WORLDPMAP[mprm.ray.mapY][mprm.ray.mapX] - 1; //1
//		subtracted
//		from it so that texture 0 can be used!
//
//		//calculate value of wallX
//		mprm.ray.wallX; //where exactly the wall was hit
//		if(mprm.ray.side == 0) mprm.ray.wallX = mprm->plr.posY + mprm.ray
//		.perpWallDist
//		* mprm.ray.rayDirY;
//		else          mprm.ray.wallX = mprm->plr.posX + mprm.ray
//		.perpWallDist
//		* mprm
//		.ray.rayDirX;
//		mprm.ray.wallX -= floor((mprm.ray.wallX));
//
//		//x coordinate on the texture
//		mprm.ray.texX = (int)(mprm.ray.wallX * (double)texWidth);
//		if(mprm.ray.side == 0 && mprm.ray.rayDirX > 0) mprm.ray.texX =
//		texWidth -
//		mprm.ray
//		.texX - 1;
//		if(mprm.ray.side == 1 && mprm.ray.rayDirY < 0) mprm.ray.texX =
//		texWidth -
//		mprm.ray
//		.texX - 1;
//
//		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
//		// How much to increase the texture coordinate per screen pixel
//		mprm.ray.step = 1.0 * texHeight / mprm.ray.lineHeight;
//		// Starting texture coordinate
//		mprm.ray.texPos = (mprm.ray.drawStart - H / 2 + mprm.ray.lineHeight /
//		2) *
//		mprm.ray
//		.step;
////		printf("x - %d\n", x);
////		printf("drawStart - %d\n", mprm.ray.drawStart);
////		printf("drawEnd - %d\n", mprm.ray.drawEnd);
//		for(int y = mprm.ray.drawStart; y < mprm.ray.drawEnd; y++)
//		{
//			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
//			mprm.ray.texY = (int)mprm.ray.texPos & (texHeight - 1);
//			mprm.ray.texPos += mprm.ray.step;
//			if(mprm.ray.side == 1) mprm.ray.color = 0xff00ff; // (mprm.ray
//			.color >>
//			1) &
//			8355711;
//			printf("x - %d, y - %d\n", x, y);
//			my_mlx_pixel_put(&mprm, x, y, 0xff0000); // mprm.ray.color);
//		}
//	}


	//speed modifiers

//	if(keyDown(SDLK_RIGHT))
//	{
//		both camera direction and camera plane must be rotated
//		double oldDirX = dirX;
//		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//		double oldPlaneX = planeX;
//		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
//	}
	//rotate to the left
//	if(keyDown(SDLK_LEFT))
//	{
//		both camera direction and camera plane must be rotated
//		double oldDirX = dirX;
//		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
//		double oldPlaneX = planeX;
//		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//	}
//	if(keyDown(SDLK_ESCAPE))
//	{
//		break;
//	}

//	my_mlx_pixel_put(&img, 0, 0, 0x00FF0000);
	mlx_hook(mprm->data.win, 2, (1L << 0), &key_press, &mprm);
	mlx_loop(mprm->data.mlx);
}