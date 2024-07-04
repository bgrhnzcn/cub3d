/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:34:37 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/05 00:34:17 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_rays(t_game *cub3d)
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

void	update_player(t_game *cub3d)
{
	t_vec2	move_dir;
	t_bool	rotate_dir;
	t_input	inputs;

	inputs = cub3d->inputs;
	move_dir = ft_vec2_norm((t_vec2){.x = inputs.a_key + inputs.d_key,
		.y = inputs.w_key + inputs.s_key});
	move_dir = ft_vec2_rot(move_dir,
		ft_rad_to_deg(-atan2(cub3d->player.dir.x, cub3d->player.dir.y)));
	move_dir = ft_vec2_inv(move_dir);
	ft_draw_line(&cub3d->debug, ft_vec2_mul(cub3d->player.pos, TILE_SIZE),
		ft_vec2_mul(ft_vec2_add(cub3d->player.pos, move_dir), TILE_SIZE),
		g_magenta);
	rotate_dir = inputs.left_key + inputs.right_key;
	player_movement(cub3d, move_dir);
	player_camera(cub3d, rotate_dir);
}

int	update(void *param)
{
	static double	last_time = 0;
	double			curr_time;
	char			*frame_rate;
	t_game			*cub3d;

	cub3d = (t_game *)param;
	curr_time = clock();
	cub3d->delta_time = (double)(curr_time - last_time) / CLOCKS_PER_SEC;
	last_time = curr_time;
	printf("delta_time: %f\n", cub3d->delta_time);
	update_player(cub3d);
	update_rays(cub3d);
	
	#if DEBUG == 1

	update_debug(cub3d);
	
	#endif

	draw_background(cub3d);
	draw_walls(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win.win,
		cub3d->mlx.img.img, 0, 0);
	frame_rate = ft_itoa((int)(1 / cub3d->delta_time));
	mlx_string_put(cub3d->mlx.mlx, cub3d->mlx.win.win, 20, 20, g_magenta.value,
		frame_rate);
	debug_log(cub3d, cub3d->log.frame_log);
	free(frame_rate);
	free(cub3d->collisions);
	free(cub3d->coll_deg);
	return (0);
}
