#include "libft/get_next_line.c"
#include "mlx_linux/mlx.h"
#include "solong.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	exit_free(t_data *data)
{
	int	i;

	i = 0;
	mlx_destroy_image(data->mlx, data->groundimg);
	mlx_destroy_image(data->mlx, data->wallimg);
	mlx_destroy_image(data->mlx, data->coinimg);
	mlx_destroy_image(data->mlx, data->playerimg);
	mlx_destroy_image(data->mlx, data->exitimg);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	free(data);
	exit(0);
}
char	**parse_map(char *filename)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;

	fd = open(filename, O_RDONLY);
	i = 0;
	map = calloc(sizeof(char *), 6);
	if (!map)
		exit(1);
	while ((line = get_next_line(fd)))
	{
		map[i] = line;
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void	calculate_map_dimensions(t_data *data)
{
	int	width;
	int	height;
	int	current_width;

	if (data->map == NULL || data->map[0] == NULL)
	{
		data->map_width = 0;
		data->map_height = 0;
		return ;
	}
	width = 0;
	height = 0;
	while (data->map[height] != NULL)
	{
		current_width = 0;
		while (data->map[height][current_width] != '\0'
			&& data->map[height][current_width] != '\n')
			current_width++;
		if (current_width > width)
			width = current_width;
		height++;
	}
	data->map_width = width;
	data->map_height = height;
}

void	render_map(t_data *data)
{
	int	x;
	int	y;
	int	block_size;
	int	canvas_width;
	int	canvas_height;

	block_size = 64;
	canvas_width = data->win_width / block_size;
	canvas_height = data->win_height / block_size;
	y = 0;
	while (y < canvas_height && data->map[y])
	{
		x = 0;
		while (x <= canvas_width && data->map[y][x] != '\n'
			&& data->map[y][x] != '\0')
		{
			if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->wallimg, x
					* block_size, y * block_size);
			else if (data->map[y][x] == 'C')
			{
				if (data->is_coins_init == 0)
					data->coins++;
				mlx_put_image_to_window(data->mlx, data->win, data->coinimg, x
					* block_size, y * block_size);
			}
			else if (data->map[y][x] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->exitimg, x
					* block_size, y * block_size);
			else if (data->map[y][x] == 'P' && data->is_player_init == 0)
			{
				mlx_put_image_to_window(data->mlx, data->win, data->playerimg, x
					* block_size, y * block_size);
				data->is_player_init = 1;
				data->player_x = x;
				data->player_y = y;
			}
			else
				mlx_put_image_to_window(data->mlx, data->win, data->groundimg, x
					* block_size, y * block_size);
			x++;
		}
		y++;
	}
}
void	draw_player(t_data *data)
{
	data->is_coins_init = 1;
	data->player_moves++;
	printf("Player moves: %d\n", data->player_moves);
	// Karakterin konumunu güncelleyin
	if (data->map[data->player_y][data->player_x] == 'C')
	{
		data->map[data->player_y][data->player_x] = '0';
		data->coins--;
	}
	mlx_clear_window(data->mlx, data->win);
	render_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->playerimg,
		data->player_x * 64, data->player_y * 64);
	if (data->map[data->player_y][data->player_x] == 'E' && data->coins == 0
		&& data->is_coins_init == 1)
	{
		printf("Congratulations! You have completed the game!\n");
		exit_free(data);
	}
}
void	move(int keycode, t_data *data)
{
	if (keycode == UP)
	{
		data->player_y -= 1;
		draw_player(data);
	}
	else if (keycode == DOWN)
	{
		data->player_y += 1;
		draw_player(data);
	}
	else if (keycode == LEFT)
	{
		data->player_x -= 1;
		draw_player(data);
	}
	else if (keycode == RIGHT)
	{
		data->player_x += 1;
		draw_player(data);
	}
}
int	key_hook(int keycode, t_data *vars)
{
	// printf("Keycode: %d\n", keycode);
	// W tuşuna basıldığında
	printf("Player x: %d, Player y: %d\n", vars->player_x, vars->player_y);
	printf("Map: %c\n", vars->map[vars->player_y][vars->player_x]);
	if (keycode == UP && vars->map[vars->player_y - 1][vars->player_x] != '1')
		move(keycode, vars);
	else if (keycode == LEFT && vars->map[vars->player_y][vars->player_x
		- 1] != '1')
		move(keycode, vars);
	else if (keycode == DOWN && vars->map[vars->player_y
		+ 1][vars->player_x] != '1')
		move(keycode, vars);
	else if (keycode == RIGHT && vars->map[vars->player_y][vars->player_x
		+ 1] != '1')
		move(keycode, vars);
	else if (keycode == ESC)
		exit_free(vars);
	return (0);
}
