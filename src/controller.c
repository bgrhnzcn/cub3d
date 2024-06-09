/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:31:37 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/09 23:58:31 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	player.tile_x = (int)(player.pos.x / TILE_SIZE);
	player.tile_y = (int)(player.pos.x / TILE_SIZE);
}

void	player_camera(t_game *cub3d, int keycode)
{
	if (keycode == LEFT_KEY)
		cub3d->player.dir = ft_vec2_rot(cub3d->player.dir, -30);
	if (keycode == RIGHT_KEY)
		cub3d->player.dir = ft_vec2_rot(cub3d->player.dir, 30);
}
