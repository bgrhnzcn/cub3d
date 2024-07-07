#ifndef CUB3D_H
# define CUB3D_H

# include <time.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "mlx.h"
# include "get_next_line_bonus.h"
# include "libft.h"

# define HEIGHT			800
# define WIDTH			800
# define TILE_SIZE		40
# define PLAYER_RAD		6
# define PLAYER_SIZE	0.2

typedef union u_vec2i
{
	struct
	{
		int	x;
		int	y;
	};
	int	data[2];
}	t_vec2i;

typedef struct s_tile_map
{
	char	*tiles;
	t_vec2i	size;
}	t_tile_map;

typedef struct s_player
{
	t_vec2	pos;
	t_vec2	dir;
	float	move_speed;
	float	camera_speed;
}	t_player;

typedef enum e_face
{
	north,
	west,
	south,
	east
}	t_face;

typedef struct s_hit
{
	t_vec2	pos;
	t_face	face;
}	t_hit;

typedef struct s_input
{
	t_bool	w_key;
	t_bool	a_key;
	t_bool	s_key;
	t_bool	d_key;
	t_bool	right_key;
	t_bool	left_key;
	t_bool	esc_key;
}	t_input;

typedef struct s_logger
{
	FILE	*frame_log;
}	t_logger;

typedef struct s_game
{
	t_mlx		mlx;
	t_mlx		debug;
	t_tile_map	map;
	t_player	player;
	t_input		inputs;
	t_img		tex_north;
	t_img		tex_west;
	t_img		tex_south;
	t_img		tex_east;
	t_hit		*collisions;
	t_logger	log;
	float		*coll_deg;
	double		delta_time;
	int			coll_count;
}	t_game;

typedef struct s_raycast
{
	float	x;
	float	y;
	int		offset;
	int		step;
	float	dist;
	t_hit	hit;
}	t_raycast;

struct s_draw_hlpr
{
	t_game	*cub3d;
	t_img	*tex;
	float	line_height;
	float	tex_x;
	int		index;
};

//---------------------- Debug --------------------------

void	init_debug(t_game *cub3d);
void	draw_tile(t_img *debug, char tile, int x, int y);
void	draw_map(t_game *cub3d);
void	draw_rays(t_game *cub3d);
void	draw_player(t_game *cub3d);
void	debug_point(t_img *img, t_vec2 point);
void	update_debug(t_game *cub3d);

//---------------------- Raycast --------------------------

void	raycast(t_game *cub3d, t_vec2 start, t_vec2 dir, t_hit *out);

//---------------------- Init --------------------------

void	init_game(t_game *cub3d);
void	init_map(t_game *cub3d);

//---------------------- Texture --------------------------

void	rotate_index(t_img *tex);
void	mirror_tex(t_img *tex);
float	get_tex_y(t_img *tex, float i, float height);
void	draw_tex_helper(int *i, float *tex_y,
	float *full_height, float *line_height);
t_color	*get_tex_data(t_img *tex, float tex_x);

//---------------------- Update --------------------------

int		update(void *param);

//----------------- Bresenham Line Algorithm -----------------------

void	ft_draw_line(t_mlx *dt, t_vec2 pt1, t_vec2 pt2, t_color color);

//----------------------- Draw -----------------

void	draw_background(t_game *cub3d);
void	draw_walls(t_game *cub3d);

//----------------------- Controller -----------------

int		key_press_handler(int keycode, t_game *cub3d);
int		key_release_handler(int keycode, t_game *cub3d);
void	player_movement(t_game *cub3d, t_vec2 dir);
void	player_camera(t_game *cub3d, t_bool rotate_dir);



#endif
