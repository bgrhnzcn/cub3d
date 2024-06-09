/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:27:56 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/09 21:00:00 by bgrhnzcn         ###   ########.fr       */
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

void	draw_rays(t_game *cub3d)
{
	raycast(cub3d);
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
