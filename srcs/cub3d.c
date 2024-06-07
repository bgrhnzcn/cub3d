/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:53:18 by buozcan           #+#    #+#             */
/*   Updated: 2024/06/07 03:30:24 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_mlx *cub3d, char tile, int x, int y)
{
	int	tile_size;

	tile_size = 64;
	for (int i = (tile_size * x) + 1; i < tile_size * (x + 1); i++)
	{
		for (int j = (tile_size * y) + 1; j < tile_size * (y + 1); j++)
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

void	draw_ray(t_game *cub3d, t_vec2 from, t_vec2 to)
{
	(void)cub3d;
	if (from.x >= 0 && from.x < WIDTH && from.y >= 0 && from.y < HEIGHT)
		if (to.x >= 0 && to.x < WIDTH && to.y >= 0 && to.y < HEIGHT)
			printf("ray:\n");
}

void	draw_player(t_game *cub3d)
{
	t_player	player;
	int			size;

	size = 5;
	player = cub3d->player;
	for (int i = player.pos.x; i < player.pos.x + size; i++)
		for (int j = player.pos.y; j < player.pos.y + size; j++)
			ft_put_pixel(&cub3d->mlx.img, i, j, g_green);
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
	draw_ray(cub3d, cub3d->player.pos, mouse_pos);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win.win,
		cub3d->mlx.img.img, 0, 0);
	return (0);
}

int	key_input(int keycode, t_game *cub3d)
{
	if (keycode == ESC_KEY)
		exit(EXIT_SUCCESS);
	if (keycode == W_KEY && cub3d->player.pos.y > 0)
		cub3d->player.pos.y -= 5;
	if (keycode == S_KEY && cub3d->player.pos.y < HEIGHT - 5)
		cub3d->player.pos.y += 5;
	if (keycode == A_KEY && cub3d->player.pos.x > 0)
		cub3d->player.pos.x -= 5;
	if (keycode == D_KEY && cub3d->player.pos.x < WIDTH - 5)
		cub3d->player.pos.x += 5;
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
