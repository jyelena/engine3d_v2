#include "cub3d.h"
#include "mlx_linux/mlx.h"

void main()
{
	void *mlx;
	void *win;
	int y;
	int x;

	mlx = NULL;
	win = NULL;
	y = 100;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 640, 480, "test");
	while (y++ < 200)
	{
		x = 100;
		while (x++ < 200)
			mlx_pixel_put(mlx, win, x, y, 0xFFFFFF);
	}
	mlx_loop(mlx);
}