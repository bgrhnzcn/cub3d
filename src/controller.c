/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:31:37 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/22 02:26:39 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_handler(int keycode, t_game *cub3d)
{
	printf("key pressed: %d\n", keycode);
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
		exit(EXIT_SUCCESS);
	return (0);
}

int	key_release_handler(int keycode, t_game *cub3d)
{
	printf("key released: %d\n", keycode);
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

void	player_movement(t_game *cub3d, t_vec2 dir)
{
	t_vec2		next_pos;

	next_pos = ft_vec2_add(cub3d->player.pos,
		ft_vec2_mul(dir, cub3d->player.move_speed));
	if ((next_pos.x > 1 && next_pos.x < (WIDTH / TILE_SIZE) - 1)
		&& (next_pos.y > 1 && next_pos.y < (HEIGHT / TILE_SIZE) - 1))
		cub3d->player.pos = next_pos;
}

void	player_camera(t_game *cub3d, t_bool rotate_dir)
{
	cub3d->player.dir = ft_vec2_rot(cub3d->player.dir,
		cub3d->player.camera_speed * rotate_dir);
}
