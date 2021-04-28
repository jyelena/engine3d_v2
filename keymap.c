#include "cub3d.h"

int 	key_press(int key, t_mprm *mprm)
{
//	printf("%d\n", key);
	if (key == 13)
		mprm->mov.up = 1;
	if (key == 1)
		mprm->mov.down = 1;
	if (key == 124)
		mprm->mov.turn_right = 1;
	if (key == 123)
		mprm->mov.turn_left = 1;
	if (key == 0)
		mprm->mov.strafe_right = 1;
	if (key == 2)
		mprm->mov.strafe_left = 1;
	if (key == 53)
		exit(0);
	return (0);
}

int 	key_release(int key, t_mprm *mprm)
{
	if (key == 13)
		mprm->mov.up = 0;
	if (key == 1)
		mprm->mov.down = 0;
	if (key == 124)
		mprm->mov.turn_right = 0;
	if (key == 123)
		mprm->mov.turn_left = 0;
	if (key == 0)
		mprm->mov.strafe_right = 0;
	if (key == 2)
		mprm->mov.strafe_left = 0;
	return (0);
}