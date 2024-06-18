/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:34:37 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/17 21:23:11 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	*update_rays(t_game *cub3d)
{
	int		i;
	float	deg;

	cub3d->coll_count = 640;
	cub3d->collisions = ft_calloc(cub3d->coll_count, sizeof (t_hit));
	if (cub3d->collisions == NULL)
		exit(EXIT_FAILURE);
	cub3d->coll_deg = ft_calloc(cub3d->coll_count, sizeof (float));
	if (cub3d->coll_deg == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	deg = -320;
	while (i < 640)
	{
		cub3d->coll_deg[i] = ft_rad_to_deg(atan(deg / 640));
		raycast(cub3d, cub3d->player.pos,
			ft_vec2_rot(cub3d->player.dir, cub3d->coll_deg[i]),
				&cub3d->collisions[i]);
		deg += 1;
		i++;
	}
}

static void	update_debug(t_game *cub3d)
{
	ft_fill_img(&cub3d->debug.win, &cub3d->debug.img, g_black);
	draw_map(cub3d);
	draw_rays(cub3d);
	draw_player(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->debug.win.win,
		cub3d->debug.img.img, 0, 0);
}

int	update(void *param)
{
	t_game	*cub3d;
	t_vec2	mouse_pos;

	cub3d = (t_game *)param;
	update_rays(cub3d);
	update_debug(cub3d);
	draw_background(cub3d);
	draw_walls(cub3d);
	mlx_mouse_get_pos(cub3d->mlx.mlx, cub3d->mlx.win.win, (int *)&mouse_pos.x, (int *)&mouse_pos.y);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win.win,
		cub3d->mlx.img.img, 0, 0);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win.win,
		cub3d->tex_north.img, 0, 0);
	free(cub3d->collisions);
	free(cub3d->coll_deg);
	return (0);
}

int	key_input(int keycode, t_game *cub3d)
{
	if (keycode == ESC_KEY)
		exit(EXIT_SUCCESS);
	player_camera(cub3d, keycode);
	player_movement(cub3d, keycode);
	return (0);
}
