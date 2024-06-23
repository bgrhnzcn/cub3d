/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:30:32 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/20 23:11:19 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	hit_vert_hlpr(t_raycast *ray, t_vec2 start, t_vec2 dir)
{
	if (dir.x < 0)
	{
		ray->x = (int)start.x;
		ray->step = -1;
		ray->offset = -1;
	}
	else
	{
		ray->x = (int)start.x + 1;
		ray->step = 1;
		ray->offset = 0;
	}
}

static t_vec2	hit_vert(t_game *cub3d, t_vec2 start, t_vec2 dir, float *dist)
{
	t_raycast	ray;

	hit_vert_hlpr(&ray, start, dir);
	while (ray.x >= 0 && ray.x < cub3d->map.size.x)
	{
		ray.y = ((dir.y / dir.x) * (ray.x - start.x)) + start.y;
		ray.hit.pos = (t_vec2){.x = ray.x, .y = ray.y};
		*dist = ft_vec2_mag(ft_vec2_sub(ray.hit.pos, start));
		if (*dist >= 100)
			return (start);
		if (ray.y >= 0 && ray.y < cub3d->map.size.y)
			if (cub3d->map.tiles[(int)(ray.x + ray.offset) +
				((int)ray.y * cub3d->map.size.x)] == '1')
				return (ray.hit.pos);
		ray.x += ray.step;
	}
	return (start);
}

static void	hit_hori_hlpr(t_raycast *ray, t_vec2 start, t_vec2 dir)
{
	if (dir.y < 0)
	{
		ray->y = (int)start.y;
		ray->step = -1;
		ray->offset = -1;
	}
	else
	{
		ray->y = (int)start.y + 1;
		ray->step = 1;
		ray->offset = 0;
	}
}

static t_vec2	hit_hori(t_game *cub3d, t_vec2 start, t_vec2 dir, float *dist)
{
	t_raycast	ray;

	hit_hori_hlpr(&ray, start, dir);
	while (ray.y > 0 && ray.y < cub3d->map.size.y)
	{
		ray.x = ((dir.x / dir.y) * (ray.y - start.y)) + start.x;
		ray.hit.pos = (t_vec2){.x = ray.x, .y = ray.y};
		*dist = ft_vec2_mag(ft_vec2_sub(ray.hit.pos, start));
		if (*dist >= 100)
			return (start);
		if (ray.x >= 0 && ray.x < cub3d->map.size.x)
			if (cub3d->map.tiles[(int)(ray.x) + (((int)ray.y + ray.offset) * cub3d->map.size.x)] == '1')
				return (ray.hit.pos);
		ray.y += ray.step;
	}
	return (start);
}

void	raycast(t_game *cub3d, t_vec2 start, t_vec2 dir, t_hit *out)
{
	t_vec2	vert;
	t_vec2	hori;
	float	dist_vert;
	float	dist_hori;

	//dir = ft_vec2_norm(dir);
	dist_vert = 0;
	dist_hori = 0;
	vert = hit_vert(cub3d, start, dir, &dist_vert);
	hori = hit_hori(cub3d, start, dir, &dist_hori);
	if (dist_hori <= dist_vert)
	{
		out->pos = hori;
		if ((start.y - hori.y) < 0)
			out->face = north;
		else
			out->face = south;
	}
	else
	{
		out->pos = vert;
		if ((start.x - vert.x) < 0)
			out->face = west;
		else
			out->face = east;
	}
}
