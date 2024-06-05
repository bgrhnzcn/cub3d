/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:53:18 by buozcan           #+#    #+#             */
/*   Updated: 2024/06/05 18:28:07 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_mlx *cub3d, char tile, int x, int y)
{
	int	tile_size;

	tile_size = 10;
	for (int i = tile_size * x; i < tile_size * (x + 1); i++)
	{
		for (int j = tile_size * y; j < tile_size * (y + 1); j++)
		{
			if (tile == '1')
			{
				ft_put_pixel(&cub3d->img, i, j, g_gray);
				printf("Working on {x: %d, y: %d}\n", i ,j);
			}
			else if (tile == '0')
			{
				ft_put_pixel(&cub3d->img, i, j, g_white);
				printf("Working on {x: %d, y: %d}\n", i ,j);
			}
		}
	}
}

void	draw_map(t_mlx *cub3d)
{
	t_tile_map	map;

	map.map_size_x = 10;
	map.map_size_y = 10;
	
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
	for (int i = 0; i < map.map_size_x; i++)
		for (int j = 0; j < map.map_size_y; j++)
			draw_tile(cub3d, tiles[i][j], i, j);
}

int	update(void *param)
{
	t_mlx	*cub3d;

	cub3d = (t_mlx *)param;
	//ft_fill_img(cub3d, (t_color){.red = 255, .alpha = 255});
	draw_map(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win.win, cub3d->img.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	cub3d;

	(void)argc;
	(void)argv;
	cub3d.mlx = mlx_init();
	cub3d.win.height = HEIGHT;
	cub3d.win.width = WIDTH;
	cub3d.win.win = mlx_new_window(cub3d.mlx, WIDTH, HEIGHT, "cub3d");
	cub3d.img.img = mlx_new_image(cub3d.mlx, cub3d.win.width, cub3d.win.height);
	cub3d.img.data = mlx_get_mlx_addr(cub3d.img.img, &cub3d.img.bits_per_pixel,
		&cub3d.img.size_line, &cub3d.img.endian);
	mlx_loop_hook(cub3d.mlx, update, &cub3d);
	mlx_loop(cub3d.mlx);
}
