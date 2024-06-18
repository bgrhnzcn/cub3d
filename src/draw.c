/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:27:56 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/18 15:22:07 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	player = cub3d->player;
	for (int i = (player.pos.x * TILE_SIZE) - PLAYER_RAD; i < (player.pos.x * TILE_SIZE) + PLAYER_RAD; i++)
		for (int j = (player.pos.y * TILE_SIZE) - PLAYER_RAD; j < (player.pos.y * TILE_SIZE) + PLAYER_RAD; j++)
			if((i >= 0 && i < WIDTH) && (j >= 0 && j < HEIGHT))
				ft_put_pixel(&cub3d->debug.img, i, j, g_green);
	ft_draw_line(&cub3d->debug, ft_vec2_mul(player.pos, TILE_SIZE),
		ft_vec2_mul(ft_vec2_add(player.pos, player.dir), TILE_SIZE), g_red);

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

void	draw_background(t_game *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (i >= 0 && i < WIDTH)
	{
		j = 0;
		while (j >= 0 && j < HEIGHT)
		{
			if(j <= HEIGHT / 2)
				ft_put_pixel(&cub3d->mlx.img, i, j, g_blue);
			else
				ft_put_pixel(&cub3d->mlx.img, i, j, g_gray);
			j++;
		}
		i++;
	}
}

void	draw_south(t_game *cub3d, float line_height, int index)
{
	int	i;
	int	offset;
	t_color	color;

	i = 0;
	offset = (HEIGHT / 2) - (line_height / 2);
	while (i < line_height)
	{
		color.value = cub3d->tex_south.data[(index % 32) + ((i % 32) * cub3d->tex_south.size_line)];
		printf("index: %i, i: %i\n", index, i);
		ft_put_pixel(&cub3d->mlx.img, index, i + offset,
			color);
		i++;
	}
}

void	draw_wall_piece(t_game *cub3d, float line_height, int index, t_face face)
{
	int	j;
	int	offset;

	offset = (HEIGHT / 2) - (line_height / 2);
	j = 0;
	while (j < line_height)
	{
		if (face == south)
			//ft_put_pixel(&cub3d->mlx.img, index, j + offset, g_red);
			draw_south(cub3d, line_height, index);
		else if (face == west)
			ft_put_pixel(&cub3d->mlx.img, index, j + offset, g_green);
		else if (face == north)
			ft_put_pixel(&cub3d->mlx.img, index, j + offset, g_dark_blue);
		else if (face == east)
			ft_put_pixel(&cub3d->mlx.img, index, j + offset, g_magenta);
		j++;
	}
}
	float	degree;

void	draw_walls(t_game *cub3d)
{
	float	line_height;
	float	ray_len;
	int		i;

	i = 0;
	while (i < cub3d->coll_count)
	{
		ray_len = ft_vec2_dist(cub3d->collisions[i].pos, cub3d->player.pos);
		line_height = HEIGHT /
			(ray_len * cos(ft_deg_to_rad(cub3d->coll_deg[i])));
		if (line_height > HEIGHT)
			line_height = HEIGHT;
		draw_wall_piece(cub3d, line_height, i, cub3d->collisions[i].face);
		i++;
	}
}
