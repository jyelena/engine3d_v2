#include "cub3d.h"

int		moving(t_mprm *mprm)
{
	double	moveSpeed;

	moveSpeed = 0.05;
    if (mprm->mov.up)
    {
      if(PMAP[(int)(mprm->plr.posY)][(int)(mprm->plr.posX + mprm->plr.dirX * moveSpeed * 1.3)]
      != '1')
      	mprm->plr.posX += mprm->plr.dirX * moveSpeed;
      if(PMAP[(int)(mprm->plr.posY + mprm->plr.dirY * moveSpeed * 1.3)][(int)(mprm->plr.posX)]
      != '1')
      	mprm->plr.posY += mprm->plr.dirY * moveSpeed;
    }
    //move backwards if no wall behind you
    if (mprm->mov.down)
    {
      if(PMAP[(int)(mprm->plr.posY)][(int)(mprm->plr.posX - mprm->plr.dirX * moveSpeed * 1.3)]
      != '1')
      	mprm->plr.posX -= mprm->plr.dirX * moveSpeed;
      if(PMAP[(int)(mprm->plr.posY - mprm->plr.dirY * moveSpeed * 1.3)][(int)
      (mprm->plr.posX)]
      != '1')
      	mprm->plr.posY -= mprm->plr.dirY * moveSpeed;
    }
    //rotate to the right
    if (mprm->mov.turn_right)
    {
      //both camera direction and camera mprm->plr.plane must be rotated
      double oldDirX = mprm->plr.dirX;
      mprm->plr.dirX = mprm->plr.dirX * cos(-moveSpeed) - mprm->plr.dirY * sin
      		(-moveSpeed);
      mprm->plr.dirY = oldDirX * sin(-moveSpeed) + mprm->plr.dirY * cos
      		(-moveSpeed);
      double oldPlaneX = mprm->plr.planeX;
      mprm->plr.planeX = mprm->plr.planeX * cos(-moveSpeed) - mprm->plr.planeY *
      		sin
      		(-moveSpeed);
      mprm->plr.planeY = oldPlaneX * sin(-moveSpeed) + mprm->plr.planeY * cos
      		(-moveSpeed);
    }
    //rotate to the left
    if (mprm->mov.turn_left)
    {
      //both camera direction and camera mprm->plr.plane must be rotated
      double oldDirX = mprm->plr.dirX;
      mprm->plr.dirX = mprm->plr.dirX * cos(moveSpeed) - mprm->plr.dirY * sin
      		(moveSpeed);
      mprm->plr.dirY = oldDirX * sin(moveSpeed) + mprm->plr.dirY * cos
      		(moveSpeed);
      double oldPlaneX = mprm->plr.planeX;
      mprm->plr.planeX = mprm->plr.planeX * cos(moveSpeed) - mprm->plr.planeY *
      		sin
      		(moveSpeed);
      mprm->plr.planeY = oldPlaneX * sin(moveSpeed) + mprm->plr.planeY * cos
      		(moveSpeed);
	}
	if (mprm->mov.strafe_right)
	{
		if (mprm->map.mp[(int)(mprm->plr.posY)][(int)(mprm->plr.posX - mprm->plr.dirY *
			(moveSpeed * 1.3))] != '1' &&
			mprm->map.mp[(int)(mprm->plr.posY)][(int)(mprm->plr.posX - mprm->plr.dirY *
			(moveSpeed * 1.3))] != '2')
			mprm->plr.posX -= mprm->plr.dirY * moveSpeed;
		if (mprm->map.mp[(int)(mprm->plr.posY + mprm->plr.dirX * (moveSpeed * 1.3))][(int)(mprm->plr.posX)]
			 != '1' &&
			mprm->map.mp[(int)(mprm->plr.posY + mprm->plr.dirX * (moveSpeed * 1.3))][(int)(mprm->plr.posX)]
			 != '2')
			mprm->plr.posY += mprm->plr.dirX * moveSpeed;
	}
	if (mprm->mov.strafe_left)
	{
		if (mprm->map.mp[(int)(mprm->plr.posY)][(int)(mprm->plr.posX + mprm->plr.dirY *
			(moveSpeed * 1.3))] != '1' &&
			mprm->map.mp[(int)(mprm->plr.posY)][(int)(mprm->plr.posX + mprm->plr.dirY *
			(moveSpeed * 1.3))] != '2')
			mprm->plr.posX += mprm->plr.dirY * moveSpeed;
		if (mprm->map.mp[(int)(mprm->plr.posY -
			mprm->plr.dirX * (moveSpeed * 1.3))][(int)(mprm->plr.posX)] !=
			'1' &&
			mprm->map.mp
			[(int)(mprm->plr.posY - mprm->plr.dirX * (moveSpeed * 1.3))][(int)
			(mprm->plr.posX)] != '2')
			mprm->plr.posY -= mprm->plr.dirX * moveSpeed;
	}
    draw_magic(mprm);
    return (0);
}

void	strafe_left(t_mprm *mprm, double speed)
{
	if (mprm->mov.strafe_right)
	{
		if (mprm->map.mp[(int)(mprm->plr.posY)][(int)(mprm->plr.posX - mprm->plr.dirY *
			(speed * 1.3))] != '1' &&
			mprm->map.mp[(int)(mprm->plr.posY)][(int)(mprm->plr.posX - mprm->plr.dirY *
			(speed * 1.3))] != '2')
			mprm->plr.posX -= mprm->plr.dirY * speed;
		if (mprm->map.mp[(int)(mprm->plr.posY + mprm->plr.dirX * (speed * 1.3))][(int)(mprm->plr.posX)]
			 != '1' &&
			mprm->map.mp[(int)(mprm->plr.posY + mprm->plr.dirX * (speed * 1.3))][(int)(mprm->plr.posX)]
			 != '2')
			mprm->plr.posY += mprm->plr.dirX * speed;
	}
}

void	strafe_right(t_mprm *mprm, double speed)
{
	if (mprm->mov.strafe_left)
	{
		if (mprm->map.mp[(int)(mprm->plr.posY)][(int)(mprm->plr.posX + mprm->plr.dirY *
			(speed * 1.3))] != '1' &&
			mprm->map.mp[(int)(mprm->plr.posY)][(int)(mprm->plr.posX + mprm->plr.dirY *
			(speed * 1.3))] != '2')
			mprm->plr.posX += mprm->plr.dirY * speed;
		if (mprm->map.mp[(int)(mprm->plr.posY -
			mprm->plr.dirX * (speed * 1.3))][(int)(mprm->plr.posX)] != '1' &&
			mprm->map.mp
			[(int)(mprm->plr.posY - mprm->plr.dirX * (speed * 1.3))][(int)(mprm->plr.posX)] != '2')
			mprm->plr.posY -= mprm->plr.dirX * speed;
	}
}