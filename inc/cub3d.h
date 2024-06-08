#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "mlx.h"
# include "get_next_line_bonus.h"
# include "libft.h"

# define HEIGHT 640
# define WIDTH 640
# define PLAYER_RAD 6

typedef struct s_tile_map
{
	char	**tiles;
	int		map_size_x : 10;
	int		map_size_y : 10;
}	t_tile_map;

typedef struct s_player
{
	t_vec2	pos;
	t_vec2	dir;
}	t_player;

typedef struct s_game
{
	t_mlx		mlx;
	t_player	player;
	t_tile_map	map;
}	t_game;

# ifdef __linux__

char	*mlx_get_mlx_addr(void *img_ptr, int *bits_per_pixel,
	int *size_line, int *endian);

# endif

void	ft_draw_line(t_mlx *dt, t_vec2 pt1, t_vec2 pt2, t_color color);

#endif
