/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:53:18 by buozcan           #+#    #+#             */
/*   Updated: 2024/06/09 01:38:54 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_mlx *cub3d, char tile, int x, int y)
{
	int	tile_size;

	tile_size = 64;
	for (int i = (tile_size * x) + 1; i < tile_size * (x + 1) - 1; i++)
	{
		for (int j = (tile_size * y) + 1; j < tile_size * (y + 1) - 1; j++)
		{
			if (tile == '1')
				ft_put_pixel(&cub3d->img, i, j, g_gray);
			else if (tile == '0')
				ft_put_pixel(&cub3d->img, i, j, g_white);
		}
	}
}

void	draw_map(t_game *cub3d)
{
	cub3d->map.map_size_x = 10;
	cub3d->map.map_size_y = 10;
	
	char	tiles[10][10] = {{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
							 {'1', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
							 {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
							 {'1', '0', '1', '0', '0', '1', '0', '0', '0', '1'},
							 {'1', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
							 {'1', '1', '1', '0', '0', '0', '0', '1', '0', '1'},
							 {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
							 {'1', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
							 {'1', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
							 {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};
	for (int i = 0; i < cub3d->map.map_size_x; i++)
		for (int j = 0; j < cub3d->map.map_size_y; j++)
			draw_tile(&cub3d->mlx, tiles[i][j], i, j);
}

void	draw_ray(t_game *cub3d, t_vec2 point, t_vec2 dir)
{
	(void)cub3d;
	if (point.x >= 0 && point.x < WIDTH && point.y >= 0 && point.y < HEIGHT)
		if (dir.x >= 0 && dir.x < WIDTH && dir.y >= 0 && dir.y < HEIGHT)
			printf("ray{point: %f, %f; dir: %f, %f}\n", point.x, point.y, dir.x, dir.y);
}

void	draw_player(t_game *cub3d)
{
	t_player	player;
	t_vec2		ray_end;

	player = cub3d->player;
	for (int i = player.pos.x - PLAYER_RAD; i < player.pos.x + PLAYER_RAD; i++)
		for (int j = player.pos.y - PLAYER_RAD; j < player.pos.y + PLAYER_RAD; j++)
			if((i >= 0 && i < WIDTH) && (j >= 0 && j < HEIGHT))
				ft_put_pixel(&cub3d->mlx.img, i, j, g_green);
	ray_end = ft_vec2_add(player.pos, player.dir);
	ft_draw_line(&cub3d->mlx, player.pos, ray_end, g_red);
	printf("ray{point: %f, %f; dir: %f, %f, end: %f, %f}\n", player.pos.x,
		player.pos.y, player.dir.x, player.dir.y, ray_end.x, ray_end.y);
}

int	update(void *param)
{
	t_game	*cub3d;
	t_vec2	mouse_pos;

	cub3d = (t_game *)param;
	ft_fill_img(&cub3d->mlx, g_black);
	draw_map(cub3d);
	draw_player(cub3d);
	mlx_mouse_get_pos(cub3d->mlx.mlx, cub3d->mlx.win.win, (int *)&mouse_pos.x, (int *)&mouse_pos.y);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win.win,
		cub3d->mlx.img.img, 0, 0);
	return (0);
}

void	player_movement(t_game *cub3d, int keycode)
{
	t_vec2		next_pos;
	t_player	player;

	player = cub3d->player;
	next_pos = player.pos;
	if (keycode == W_KEY)
		next_pos = ft_vec2_add(player.pos, player.dir);
	if (keycode == S_KEY)
		next_pos = ft_vec2_sub(player.pos, player.dir);
	if (keycode == A_KEY)
		next_pos = ft_vec2_add(player.pos,
			ft_vec2_rot(player.dir, -90));
	if (keycode == D_KEY)
		next_pos = ft_vec2_add(player.pos,
			ft_vec2_rot(player.dir, 90));
	if ((next_pos.x >= 0 && next_pos.x < WIDTH)
		&& (next_pos.y >= 0 && next_pos.y < HEIGHT))
		cub3d->player.pos = next_pos;
}

void	player_camera(t_game *cub3d, int keycode)
{
	if (keycode == LEFT_KEY)
		cub3d->player.dir = ft_vec2_rot(cub3d->player.dir, -30);
	if (keycode == RIGHT_KEY)
		cub3d->player.dir = ft_vec2_rot(cub3d->player.dir, 30);
}

int	key_input(int keycode, t_game *cub3d)
{
	if (keycode == ESC_KEY)
		exit(EXIT_SUCCESS);
	player_camera(cub3d, keycode);
	player_movement(cub3d, keycode);
	return (0);
}

char	*mlx_get_mlx_addr(void *img_ptr, int *bits_per_pixel,
	int *size_line, int *endian)
{
	return (mlx_get_data_addr(img_ptr, bits_per_pixel, size_line,
		endian));
}

void	init_player(t_game *cub3d)
{
	cub3d->player.pos.x = 400;
	cub3d->player.pos.y = 200;
	cub3d->player.dir.x = 0;
	cub3d->player.dir.y = -10;
}

int	main(int argc, char **argv)
{
	t_game	cub3d;

	(void)argc;
	(void)argv;
	init_player(&cub3d);
	cub3d.mlx.mlx = mlx_init();
	cub3d.mlx.win.height = HEIGHT;
	cub3d.mlx.win.width = WIDTH;
	cub3d.mlx.win.win = mlx_new_window(cub3d.mlx.mlx, WIDTH, HEIGHT, "cub3d");
	cub3d.mlx.img.img = mlx_new_image(cub3d.mlx.mlx, cub3d.mlx.win.width, cub3d.mlx.win.height);
	cub3d.mlx.img.data = mlx_get_mlx_addr(cub3d.mlx.img.img, &cub3d.mlx.img.bits_per_pixel,
		&cub3d.mlx.img.size_line, &cub3d.mlx.img.endian);
	mlx_do_key_autorepeaton(cub3d.mlx.mlx);
	mlx_loop_hook(cub3d.mlx.mlx, update, &cub3d);
	mlx_hook(cub3d.mlx.win.win, 2, 1, key_input, &cub3d);
	mlx_loop(cub3d.mlx.mlx);
}
