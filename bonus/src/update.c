/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:34:37 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/23 20:25:28 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_rays(t_game *cub3d)
{
	int		i;
	float	deg_step;

	i = 0;
	deg_step = -(WIDTH / 2);
	while (i < WIDTH)
	{
		cub3d->coll_deg[i] = ft_rad_to_deg(atan(deg_step / WIDTH));
		raycast(cub3d, cub3d->player.pos,
			ft_vec2_rot(cub3d->player.dir, cub3d->coll_deg[i]),
			&cub3d->collisions[i]);
		deg_step += 1;
		i++;
	}
}

void	update_player(t_game *cub3d)
{
	t_vec2	move_dir;
	t_bool	rotate_dir;
	t_input	inputs;

	inputs = cub3d->inputs;
	move_dir = (t_vec2){.x = inputs.a_key + inputs.d_key,
		.y = inputs.w_key + inputs.s_key};
	move_dir = ft_vec2_norm(move_dir);
	move_dir = ft_vec2_rot(move_dir,
			ft_rad_to_deg(-atan2(cub3d->player.dir.x, cub3d->player.dir.y)));
	move_dir = ft_vec2_inv(move_dir);
	rotate_dir = inputs.left_key + inputs.right_key;
	player_camera(cub3d, rotate_dir);
	player_movement(cub3d, move_dir);
}

int	update(void *param)
{
	t_game	*cub3d;

	cub3d = (t_game *)param;
	update_player(cub3d);
	update_rays(cub3d);
	draw_background(cub3d);
	draw_walls(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win.win,
		cub3d->mlx.img.img, 0, 0);
	draw_minimap(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win.win,
		cub3d->mini_map.img, 0, 0);
	return (0);
}
