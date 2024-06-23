/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:27:56 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/23 12:53:21 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	draw_south(t_game *cub3d, float line_height, int index, float tex_x)
{
	int		i;
	float	tex_y;
	float	full_height;
	t_color	*data;

	data = cub3d->tex_south.data +
		((int)ft_lerp(tex_x, 0, cub3d->tex_south.size_line) *
			cub3d->tex_south.size_line);
	i = 0;
	tex_y = 0;
	full_height = line_height;
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	while (i < line_height)
	{
		if (full_height > HEIGHT)
		{
			tex_y = ft_lerp(ft_normalize(i + ((full_height - HEIGHT) / 2), 0,
				full_height),
				0 , cub3d->tex_south.size_line);
		}
		else
			tex_y = ft_lerp(ft_normalize(i, 0,
				line_height),
				0, cub3d->tex_south.size_line);
		if (tex_y >= cub3d->tex_south.size_line)
			tex_y = cub3d->tex_south.size_line - 1;
		ft_put_pixel(&cub3d->mlx.img, index,
			i + (HEIGHT - line_height) / 2,
			data[(int)tex_y]);
		i++;
	}
}

void	draw_north(t_game *cub3d, float line_height, int index, float tex_x)
{
	int		i;
	float	tex_y;
	float	full_height;
	t_color	*data;

	data = cub3d->tex_north.data +
		((int)ft_lerp(tex_x, 0, cub3d->tex_north.size_line) *
			cub3d->tex_north.size_line);
	i = 0;
	tex_y = 0;
	full_height = line_height;
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	while (i < line_height)
	{
		if (full_height > HEIGHT)
		{
			tex_y = ft_lerp(ft_normalize(i + ((full_height - HEIGHT) / 2), 0,
				full_height),
				0 , cub3d->tex_north.size_line);
		}
		else
			tex_y = ft_lerp(ft_normalize(i, 0,
				line_height),
				0, cub3d->tex_north.size_line);
		if (tex_y >= cub3d->tex_north.size_line)
			tex_y = cub3d->tex_north.size_line - 1;
		ft_put_pixel(&cub3d->mlx.img, index,
			i + (HEIGHT - line_height) / 2,
			data[(int)tex_y]);
		i++;
	}
}

void	draw_west(t_game *cub3d, float line_height, int index, float tex_x)
{
	int		i;
	float	tex_y;
	float	full_height;
	t_color	*data;

	data = cub3d->tex_west.data +
		((int)ft_lerp(tex_x, 0, cub3d->tex_west.size_line) *
			cub3d->tex_west.size_line);
	i = 0;
	tex_y = 0;
	full_height = line_height;
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	while (i < line_height)
	{
		if (full_height > HEIGHT)
		{
			tex_y = ft_lerp(ft_normalize(i + ((full_height - HEIGHT) / 2), 0,
				full_height),
				0 , cub3d->tex_west.size_line);
		}
		else
			tex_y = ft_lerp(ft_normalize(i, 0,
				line_height),
				0, cub3d->tex_west.size_line);
		if (tex_y >= cub3d->tex_west.size_line)
			tex_y = cub3d->tex_west.size_line - 1;
		ft_put_pixel(&cub3d->mlx.img, index,
			i + (HEIGHT - line_height) / 2,
			data[(int)tex_y]);
		i++;
	}
}

void	draw_east(t_game *cub3d, float line_height, int index, float tex_x)
{
	int		i;
	float	tex_y;
	float	full_height;
	t_color	*data;

	data = cub3d->tex_east.data +
		((int)ft_lerp(tex_x, 0, cub3d->tex_east.size_line) *
			cub3d->tex_east.size_line);
	i = 0;
	tex_y = 0;
	full_height = line_height;
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	while (i < line_height)
	{
		if (full_height > HEIGHT)
		{
			tex_y = ft_lerp(ft_normalize(i + ((full_height - HEIGHT) / 2), 0,
				full_height),
				0 , cub3d->tex_east.size_line);
		}
		else
			tex_y = ft_lerp(ft_normalize(i, 0,
				line_height),
				0, cub3d->tex_east.size_line);
		if (tex_y >= cub3d->tex_east.size_line)
			tex_y = cub3d->tex_east.size_line - 1;
		ft_put_pixel(&cub3d->mlx.img, index,
			i + (HEIGHT - line_height) / 2,
			data[(int)tex_y]);
		i++;
	}
}

void	draw_wall_piece(t_game *cub3d, float line_height, int index, t_face face)
{
	float	tex_x;

	if (face == south)
	{
		tex_x = cub3d->collisions[index].pos.x -
			(int)cub3d->collisions[index].pos.x;
		draw_south(cub3d, line_height, index, tex_x);
	}
	if (face == west)
	{
		tex_x = cub3d->collisions[index].pos.y -
			(int)cub3d->collisions[index].pos.y;
		draw_west(cub3d, line_height, index, tex_x);
	}
	if (face == north)
	{
		tex_x = cub3d->collisions[index].pos.x -
			(int)cub3d->collisions[index].pos.x;
		draw_north(cub3d, line_height, index, tex_x);
	}
	if (face == east)
	{
		tex_x = cub3d->collisions[index].pos.y -
			(int)cub3d->collisions[index].pos.y;
		draw_east(cub3d, line_height, index, tex_x);
	}

}

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
		draw_wall_piece(cub3d, line_height, i, cub3d->collisions[i].face);
		i++;
	}
}
