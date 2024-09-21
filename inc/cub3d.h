/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 00:37:57 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/12 00:37:58 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "mlx.h"
# include "get_next_line_bonus.h"
# include "libft.h"

# define HEIGHT			800
# define WIDTH			800
# define PLAYER_RAD		6
# define PLAYER_SIZE	0.2
# define MAX_RAY_LENGHT	100

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
	float	move_speed;
	float	camera_speed;
	t_vec2	pos;
	t_vec2	dir;
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
	t_face	face;
	t_vec2	pos;
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

typedef struct s_parse
{
	char		*map_path;
	char		*no_pth;
	char		*we_pth;
	char		*so_pth;
	char		*ea_pth;
	int			retval;
}	t_parse;

typedef struct s_game
{
	t_hit		collisions[WIDTH];
	float		coll_deg[WIDTH];
	t_tile_map	map;
	t_player	player;
	t_input		inputs;
	t_img		tex_north;
	t_img		tex_west;
	t_img		tex_south;
	t_img		tex_east;
	t_color		floor;
	t_color		ceil;
	t_mlx		mlx;
	t_bool		fl_cntrl;
	t_bool		cl_cntrl;
	t_parse		parse;
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

//---------------------- Raycast --------------------------

void	raycast(t_game *cub3d, t_vec2 start, t_vec2 dir, t_hit *out);

//---------------------- Init --------------------------

void	init_game(t_game *cub3d);

//---------------------- Texture --------------------------

void	rotate_index(t_img *tex);
void	mirror_tex(t_img *tex);
float	get_tex_y(t_img *tex, float i, float height);
void	draw_tex_helper(int *i, float *tex_y,
			float *full_height, float *line_height);
t_color	*get_tex_data(t_img *tex, float tex_x);

//---------------------- Update --------------------------

int		update(void *param);

//----------------------- Draw -----------------

void	draw_background(t_game *cub3d);
void	draw_walls(t_game *cub3d);

//----------------------- Controller -----------------

int		key_press_handler(int keycode, t_game *cub3d);
int		key_release_handler(int keycode, t_game *cub3d);
void	player_movement(t_game *cub3d, t_vec2 dir);
void	player_camera(t_game *cub3d, t_bool rotate_dir);

//----------------------- Map -----------------

int		take_all_things_from_doc(t_game *cub3d);
int		control_names_and_values(char *sub, t_game *cub3d, int status);
void	free_dpointer(char	**arr);
int		take_and_control_map(char	**res, t_game *cub3d);
int		take_line_len(char	*str);
void	check_for_spaces(char **line, t_game *cub3d, int j);
void	take_max_x(char **res, t_game *cub3d);
void	size_of_map(char ***res, int fd);
char	**turn_map_list2array(t_list *list, int size);

//---------------- Map Control ----------------

int		control_map(t_game	*cub3d, char **map);
int		control_extension(char	*path);
int		check_same(char *str, char *str2);
int		find_first_one(char *str);
int		find_last_one(char *str);
int		check_for_undefined_char(char **map);
char	**copy_map(char **map);
int		take_map_size(char **map);
void	take_player_pos(t_game *cub3d, char **map);
void	free_if(void *content);

#endif
