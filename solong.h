#ifndef SO_LONG_H
# define SO_LONG_H
# define HEIGHT 64
# define WIDTH 64
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ESC 65307
typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*groundimg;
	void	*wallimg;
	void	*playerimg;
	void	*exitimg;
	void	*coinimg;
	char	**map;
	int		win_width;
	int		win_height;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		is_player_init;
	int		player_moves;
	int		coins;
	int		is_coins_init;
}			t_data;

void		render_map(t_data *data);
char		**parse_map(char *filename);
void		calculate_map_dimensions(t_data *data);
void		draw_player(t_data *vars);
int			key_hook(int keycode, t_data *vars);
void		exit_free(t_data *data);
#endif