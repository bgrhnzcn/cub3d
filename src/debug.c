/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:52:19 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/05 18:52:46 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_debug(t_game *cub3d)
{
	cub3d->debug.win.height = HEIGHT;
	cub3d->debug.win.width = WIDTH;
	cub3d->debug.win.win = mlx_new_window(cub3d->mlx.mlx,
		WIDTH, HEIGHT, "cub3d - map");
	cub3d->debug.img.img = mlx_new_image(cub3d->mlx.mlx,
		cub3d->mlx.win.width, cub3d->mlx.win.height);
	cub3d->debug.img.data = (t_color *)mlx_get_data_addr(cub3d->debug.img.img,
		&cub3d->debug.img.bits_per_pixel,
		&cub3d->debug.img.size_line, &cub3d->debug.img.endian);
	cub3d->debug.img.size_line /= 4;
}

void	draw_tile(t_img *debug, char tile, int x, int y)
{
	for (int i = (TILE_SIZE * x) + 1; i < TILE_SIZE * (x + 1) - 1; i++)
	{
		for (int j = (TILE_SIZE * y) + 1; j < TILE_SIZE * (y + 1) - 1; j++)
		{
			if (tile == '1')
				ft_put_pixel(debug, i, j, g_black);
			else if (tile == '0')
				ft_put_pixel(debug, i, j, g_gray);
		}
	}
}

void	draw_map(t_game *cub3d)
{
	for (int j = 0; j < cub3d->map.size.y; j++)
		for (int i = 0; i < cub3d->map.size.x; i++)
			draw_tile(&cub3d->debug.img, cub3d->map.tiles[i + cub3d->map.size.x * j], i, j);
}

void	draw_rays(t_game *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->coll_count)
	{
		debug_point(&cub3d->debug.img, cub3d->collisions[i].pos);
		ft_draw_line(&cub3d->debug,
			ft_vec2_mul(cub3d->player.pos, TILE_SIZE),
			ft_vec2_mul(cub3d->collisions[i].pos, TILE_SIZE), g_yellow);
		i++;
	}
}

void	draw_player(t_game *cub3d)
{
	t_player	player;
	t_input		inputs;
	t_vec2		move_dir;

	inputs = cub3d->inputs;
	player = cub3d->player;
	for (int i = (player.pos.x * TILE_SIZE) - PLAYER_RAD; i < (player.pos.x * TILE_SIZE) + PLAYER_RAD; i++)
		for (int j = (player.pos.y * TILE_SIZE) - PLAYER_RAD; j < (player.pos.y * TILE_SIZE) + PLAYER_RAD; j++)
			if((i >= 0 && i < WIDTH) && (j >= 0 && j < HEIGHT))
				ft_put_pixel(&cub3d->debug.img, i, j, g_green);
	ft_draw_line(&cub3d->debug, ft_vec2_mul(player.pos, TILE_SIZE),
		ft_vec2_mul(ft_vec2_add(player.pos, player.dir), TILE_SIZE), g_red);
	move_dir = ft_vec2_norm((t_vec2){.x = inputs.a_key + inputs.d_key,
		.y = inputs.w_key + inputs.s_key});
	move_dir = ft_vec2_rot(move_dir,
		ft_rad_to_deg(-atan2(cub3d->player.dir.x, cub3d->player.dir.y)));
	move_dir = ft_vec2_inv(move_dir);
	ft_draw_line(&cub3d->debug, ft_vec2_mul(cub3d->player.pos, TILE_SIZE),
		ft_vec2_mul(ft_vec2_add(cub3d->player.pos, move_dir), TILE_SIZE),
		g_magenta);
}

void	debug_point(t_img *img, t_vec2 point)
{
	if (point.x < 0 && (point.x * TILE_SIZE) >= WIDTH)
		if (point.y < 0 && (point.y * TILE_SIZE) >= HEIGHT)
			return ;
	for (int i = (point.x * TILE_SIZE) - 2; i < (point.x * TILE_SIZE) + 2; i++)
		for (int j = (point.y * TILE_SIZE) - 2; j < (point.y * TILE_SIZE) + 2; j++)
			if((i >= 0 && i < WIDTH) && (j >= 0 && j < HEIGHT))
				ft_put_pixel(img, i, j, g_cyan);
}

void	update_debug(t_game *cub3d)
{
	ft_fill_img(&cub3d->debug.win, &cub3d->debug.img, g_black);
	draw_map(cub3d);
	draw_rays(cub3d);
	draw_player(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->debug.win.win,
		cub3d->debug.img.img, 0, 0);
}

FILE	*create_logger(char *log_name)
{
	FILE	*fd;
	char	log_path[100] = "./log/";
	char *	time_stamp;
	struct	tm *asd;
	
	asd = localtime(&(time_t){time(NULL)});
	time_stamp = asctime(asd);
	ft_strlcat(log_path, log_name, 100);
	ft_strlcat(log_path, "-", 100);
	ft_strlcat(log_path, time_stamp, 100);
	fd = fopen(log_path, "w");
	return (fd);
}

void	remove_logger(FILE *fd)
{
	if (fd != NULL)
		fclose(fd);
}

void	debug_log(t_game *cub3d, FILE *fd)
{
	if (fd == NULL)
		printf("Can't access file no: %d. \
			Please check the file is exist and have proper permisions\n",
			fd->_fileno);
	else
		fprintf(fd, "FrameRate: %d\n",
			(int)(1 / cub3d->delta_time));
}
