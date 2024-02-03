#include "mlx_linux/mlx.h"
#include "solong.h"
#include <stdio.h>
#include <stdlib.h>

void	init_images(t_data *data, int width, int height)
{
	data->coins = 0;
	data->player_moves = 0;
	data->groundimg = mlx_xpm_file_to_image(data->mlx, "assets/ground.xpm",
			&width, &height);
	data->wallimg = mlx_xpm_file_to_image(data->mlx, "assets/wall.xpm", &width,
			&height);
	data->coinimg = mlx_xpm_file_to_image(data->mlx, "assets/coin.xpm", &width,
			&height);
	data->playerimg = mlx_xpm_file_to_image(data->mlx, "assets/player.xpm",
			&width, &height);
	data->exitimg = mlx_xpm_file_to_image(data->mlx, "assets/exit.xpm", &width,
			&height);
	if (!data->groundimg || !data->wallimg || !data->coinimg || !data->playerimg
		|| !data->exitimg)
	{
		exit(1);
	}
}
void	init_game(void)
{
	t_data	*data;
	int		width;
	int		height;

	width = WIDTH;
	height = HEIGHT;
	data = calloc(sizeof(t_data), 1);
	if (!data)
		exit(1);
	data->mlx = mlx_init();
	data->map = parse_map("maps/map1.ber");
	calculate_map_dimensions(data);
	data->win_width = data->map_width * width;
	data->win_height = data->map_height * height;
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height,
			"Hello world!");
	init_images(data, width, height);
	render_map(data);
	mlx_key_hook(data->win, key_hook, data);
	mlx_loop(data->mlx);
}
int	main(void)
{
	init_game();

	return (0);
}