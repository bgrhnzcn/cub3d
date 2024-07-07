/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:31:37 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/07 19:05:48 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_handler(int keycode, t_game *cub3d)
{
	if (keycode == W_KEY)
		cub3d->inputs.w_key = -1;
	if (keycode == A_KEY)
		cub3d->inputs.a_key = -1;
	if (keycode == S_KEY)
		cub3d->inputs.s_key = 1;
	if (keycode == D_KEY)
		cub3d->inputs.d_key = 1;
	if (keycode == LEFT_KEY)
		cub3d->inputs.left_key = -1;
	if (keycode == RIGHT_KEY)
		cub3d->inputs.right_key = 1;
	if (keycode == ESC_KEY)
	{
		#if DEBUG == 1
		
		remove_logger(cub3d->log.frame_log);
		
		#endif
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	key_release_handler(int keycode, t_game *cub3d)
{
	if (keycode == W_KEY)
		cub3d->inputs.w_key = 0;
	if (keycode == A_KEY)
		cub3d->inputs.a_key = 0;
	if (keycode == S_KEY)
		cub3d->inputs.s_key = 0;
	if (keycode == D_KEY)
		cub3d->inputs.d_key = 0;
	if (keycode == LEFT_KEY)
		cub3d->inputs.left_key = 0;
	if (keycode == RIGHT_KEY)
		cub3d->inputs.right_key = 0;
	return (0);
}

void	player_collision(t_game *cub3d, t_vec2 next_pos)
{
	if (next_pos.x > cub3d->player.pos.x)
	{
		if (cub3d->map.tiles[(int)(next_pos.x + PLAYER_SIZE) + ((int)cub3d->player.pos.y * cub3d->map.size.x)] != '1')
			cub3d->player.pos.x = next_pos.x;
	}
	else
	{
		if (cub3d->map.tiles[(int)(next_pos.x - PLAYER_SIZE) + ((int)cub3d->player.pos.y * cub3d->map.size.x)] != '1')
			cub3d->player.pos.x = next_pos.x;
	}
	if (next_pos.y > cub3d->player.pos.y)
	{
		if (cub3d->map.tiles[(int)cub3d->player.pos.x + ((int)(next_pos.y + PLAYER_SIZE) * cub3d->map.size.x)] != '1')
			cub3d->player.pos.y = next_pos.y;
	}
	else
	{
		if (cub3d->map.tiles[(int)cub3d->player.pos.x + ((int)(next_pos.y - PLAYER_SIZE) * cub3d->map.size.x)] != '1')
			cub3d->player.pos.y = next_pos.y;
	}
}

void	player_movement(t_game *cub3d, t_vec2 dir)
{
	t_vec2		next_pos;

	next_pos = ft_vec2_add(cub3d->player.pos,
		ft_vec2_mul(dir, cub3d->player.move_speed * cub3d->delta_time));
	player_collision(cub3d, next_pos);
	//if (next_pos.x > 1.2 && next_pos.x < (WIDTH / TILE_SIZE) - 1.2)
	//	cub3d->player.pos.x = next_pos.x;
	//if (next_pos.y > 1.2 && next_pos.y < (HEIGHT / TILE_SIZE) - 1.2)
	//	cub3d->player.pos.y = next_pos.y;
}

void	player_camera(t_game *cub3d, t_bool rotate_dir)
{
	cub3d->player.dir = ft_vec2_rot(cub3d->player.dir,
		cub3d->player.camera_speed * rotate_dir * cub3d->delta_time);
}
