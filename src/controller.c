/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:31:37 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/17 15:36:45 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_movement(t_game *cub3d, int keycode)
{
	t_vec2		next_pos;
	t_player	player;
	float		speed;

	player = cub3d->player;
	next_pos = player.pos;
	speed = 0.1;
	if (keycode == W_KEY)
		next_pos = ft_vec2_add(player.pos, ft_vec2_mul(player.dir, speed));
	if (keycode == S_KEY)
		next_pos = ft_vec2_sub(player.pos, ft_vec2_mul(player.dir, speed));
	if (keycode == A_KEY)
		next_pos = ft_vec2_add(player.pos,
			ft_vec2_mul(ft_vec2_rot(player.dir, -90), speed));
	if (keycode == D_KEY)
		next_pos = ft_vec2_add(player.pos,
			ft_vec2_mul(ft_vec2_rot(player.dir, 90), speed));
	if ((next_pos.x >= 0 && next_pos.x < WIDTH / TILE_SIZE)
		&& (next_pos.y >= 0 && next_pos.y < HEIGHT / TILE_SIZE))
		cub3d->player.pos = next_pos;
	player.tile_x = (int)(player.pos.x);
	player.tile_y = (int)(player.pos.y);
}

void	player_camera(t_game *cub3d, int keycode)
{
	if (keycode == LEFT_KEY)
		cub3d->player.dir = ft_vec2_rot(cub3d->player.dir, -1);
	if (keycode == RIGHT_KEY)
		cub3d->player.dir = ft_vec2_rot(cub3d->player.dir, 1);
}
