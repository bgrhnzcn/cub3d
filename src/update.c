/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:34:37 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/09 16:30:27 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update(void *param)
{
	t_game	*cub3d;
	t_vec2	mouse_pos;

	cub3d = (t_game *)param;
	ft_fill_img(&cub3d->mlx, g_black);
	draw_map(cub3d);
	draw_player(cub3d);
	draw_rays(cub3d);
	mlx_mouse_get_pos(cub3d->mlx.mlx, cub3d->mlx.win.win, (int *)&mouse_pos.x, (int *)&mouse_pos.y);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win.win,
		cub3d->mlx.img.img, 0, 0);
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
