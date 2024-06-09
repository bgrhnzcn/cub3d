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
# define TILE_SIZE 64
# define PLAYER_RAD 6

typedef struct s_tile_map
{
	char	**tiles;
	int		map_size_x : 10;
	int		map_size_y : 10;
}	t_tile_map;

typedef struct s_player
{
	int		tile_x;
	int		tile_y;
	t_vec2	pos;
	t_vec2	dir;
}	t_player;

typedef struct s_game
{
	t_mlx		mlx;
	t_player	player;
	t_tile_map	map;
}	t_game;

typedef struct s_raycast
{
	int			ray_cell_x;
	int			ray_cell_y;
	int			step_x;
	int			step_y;
	t_vec2		delta;
	t_vec2		ray_dir;
	t_vec2		len;
	t_player	player;
	t_bool		is_wall;
}	t_raycast;


# ifdef __linux__

char	*mlx_get_mlx_addr(void *img_ptr, int *bits_per_pixel,
	int *size_line, int *endian);

# endif

//---------------------- Raycast --------------------------
t_vec2	raycast(t_game *cub3d);

//---------------------- Init --------------------------
void	init_player(t_game *cub3d);

//---------------------- Update --------------------------
int	update(void *param);
int	key_input(int keycode, t_game *cub3d);

//----------------- Bresenham Line Algorithm -----------------------
void	ft_draw_line(t_mlx *dt, t_vec2 pt1, t_vec2 pt2, t_color color);

//----------------------- Draw -----------------
void	draw_tile(t_mlx *cub3d, char tile, int x, int y);
void	draw_map(t_game *cub3d);
void	draw_rays(t_game *cub3d);
void	draw_player(t_game *cub3d);

//----------------------- Controller -----------------
void	player_movement(t_game *cub3d, int keycode);
void	player_camera(t_game *cub3d, int keycode);


#endif
