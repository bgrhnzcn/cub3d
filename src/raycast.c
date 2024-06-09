/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:30:32 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/10 00:07:25 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vec2	get_differantiation(t_vec2 ray)
{
	t_vec2	delta;

	delta.x = sqrtf(1 + powf(ray.y / ray.x, 2));
	delta.y = sqrtf(1 + powf(ray.x / ray.y, 2));
	return (delta);
}

static void	get_steps(t_raycast *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step_x = -1;
		ray->len.x = (ray->player.pos.x - (float)ray->ray_cell_x) * ray->delta.x;
	}
	else
	{
		ray->step_x = 1;
		ray->len.x = ((float)(ray->ray_cell_x + 1) - ray->player.pos.x) * ray->delta.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step_y = -1;
		ray->len.y = (ray->player.pos.y - (float)ray->ray_cell_y) * ray->delta.y;
	}
	else
	{
		ray->step_y = 1;
		ray->len.y = ((float)(ray->ray_cell_y + 1) - ray->player.pos.y) * ray->delta.y;
	}
}

static const t_vec2	g_vec2_null = (t_vec2){.x = 0, .y = 0};

t_vec2	raycast(t_game *cub3d)
{
	t_raycast	ray;
	int			mouse_x;
	int			mouse_y;
	t_vec2		coll = g_vec2_null;
	float		max_dist = 100;
	float		dist = 0;

	mlx_mouse_get_pos(cub3d->mlx.mlx, cub3d->mlx.win.win, &mouse_x, &mouse_y);
	ray.player = cub3d->player;
	ray.ray_dir = ft_vec2_norm(ft_vec2_sub(ft_vec2_set(mouse_x, mouse_y), ray.player.pos));
	ray.delta = get_differantiation(ray.ray_dir);
	ray.player.tile_x = (int)ray.player.pos.x;
	ray.player.tile_y = (int)ray.player.pos.y;
	get_steps(&ray);
	ray.is_wall = false;
	while (!ray.is_wall && dist < max_dist)
	{
		if (ray.len.x < ray.len.y)
		{
			ray.ray_cell_x += ray.step_x;
			dist = ray.len.x;
			ray.len.x += ray.delta.x;
		}
		else
		{
			ray.ray_cell_y += ray.step_y;
			dist = ray.len.y;
			ray.len.y += ray.delta.y;
		}
		if (ray.ray_cell_x >= 0 && ray.ray_cell_x < cub3d->map.map_size_x && ray.ray_cell_y >= 0 && ray.ray_cell_y < cub3d->map.map_size_y)
		if (cub3d->map.tiles[ray.ray_cell_x][ray.ray_cell_y] == 1)
			ray.is_wall = true;
		if (ray.is_wall)
			coll = ft_vec2_add(ray.player.pos, (ft_vec2_mul(ray.ray_dir, dist)));
	}
	printf("delta.x: %f, delta.y: %f\n", ray.delta.x, ray.delta.y);
	return (coll);
}