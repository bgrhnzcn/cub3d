/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:36:34 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/03 18:05:44 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *cub3d)
{
	cub3d->player.pos.x = 4.5;
	cub3d->player.pos.y = 5.5;
	cub3d->player.dir.x = 0;
	cub3d->player.dir.y = 1;
	cub3d->player.move_speed = 10;
	cub3d->player.camera_speed = 100;
}

void	init_map(t_game *cub3d)
{
	cub3d->map.size.x = 20;
	cub3d->map.size.y = 20;
	cub3d->map.tiles = malloc(sizeof (char) *
		cub3d->map.size.x * cub3d->map.size.y);
	if (cub3d->map.tiles == NULL)
		exit(EXIT_FAILURE);
	ft_memcpy(cub3d->map.tiles, &(char[400]){'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										     '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
										     '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
										     '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
										     '1', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
										     '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
										     '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
										     '1', '1', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										     '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
											 '1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
											 '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1',
											 '1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
											 '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
											 '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
											 '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
											 '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
											 '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
											 '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
											 '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
										     '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',}, 400);
}

static void	init_tex(t_game *cub3d, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub3d->mlx.mlx, path,
		&tex->size_line, &tex->line_count);
	if (tex->img == NULL)
		exit(EXIT_FAILURE);
	tex->data = (t_color *)mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
		&tex->size_line, &tex->endian);
	tex->size_line /= (tex->bits_per_pixel / 8);
	rotate_index(tex);
}

void	init_game(t_game *cub3d)
{
	cub3d->inputs = (t_input){0};
	cub3d->mlx.mlx = mlx_init();
	cub3d->mlx.win.height = HEIGHT;
	cub3d->mlx.win.width = WIDTH;
	cub3d->mlx.win.win = mlx_new_window(cub3d->mlx.mlx,
		WIDTH, HEIGHT, "cub3d - game");
	cub3d->mlx.img.img = mlx_new_image(cub3d->mlx.mlx,
		cub3d->mlx.win.width, cub3d->mlx.win.height);
	cub3d->mlx.img.data = (t_color *)mlx_get_data_addr(cub3d->mlx.img.img,
		&cub3d->mlx.img.bits_per_pixel,
		&cub3d->mlx.img.size_line, &cub3d->mlx.img.endian);
		cub3d->mlx.img.size_line /= 4;
	init_tex(cub3d, &cub3d->tex_south, "textures/Icon6.xpm");
	init_tex(cub3d, &cub3d->tex_west, "textures/Icon16.xpm");
	init_tex(cub3d, &cub3d->tex_north, "textures/Icon2.xpm");
	mirror_tex(&cub3d->tex_north);
	init_tex(cub3d, &cub3d->tex_east, "textures/Icon10.xpm");
	mirror_tex(&cub3d->tex_east);

	#if DEBUG == 1
	
	init_debug(cub3d);
	
	#endif
	
	init_player(cub3d);
	init_map(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win.win,
		cub3d->mlx.img.img, 0, 0);
	mlx_do_key_autorepeatoff(cub3d->mlx.mlx);
}
