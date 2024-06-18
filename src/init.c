/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:36:34 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/18 15:00:21 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *cub3d)
{
	cub3d->player.pos.x = 3.5;
	cub3d->player.pos.y = 5.5;
	cub3d->player.dir.x = 0;
	cub3d->player.dir.y = -1;
}

void	init_map(t_game *cub3d)
{
	cub3d->map.size.x = 10;
	cub3d->map.size.y = 10;
	cub3d->map.tiles = malloc(sizeof (char) *
		cub3d->map.size.x * cub3d->map.size.y);
	if (cub3d->map.tiles == NULL)
		exit(EXIT_FAILURE);
	ft_memcpy(cub3d->map.tiles, &(char[100]){'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										     '1', '0', '1', '0', '0', '0', '0', '0', '0', '1',
										     '1', '0', '0', '0', '0', '0', '0', '0', '0', '1',
										     '1', '0', '0', '0', '0', '0', '0', '0', '0', '1',
										     '1', '0', '0', '0', '0', '0', '0', '1', '0', '1',
										     '1', '1', '0', '0', '0', '0', '0', '0', '0', '1',
										     '1', '0', '0', '0', '0', '0', '0', '0', '0', '1',
										     '1', '1', '0', '0', '1', '0', '1', '1', '1', '1',
										     '1', '0', '0', '0', '0', '0', '0', '0', '0', '1',
										     '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',}, 100);
}

void	init_debug(t_game *cub3d)
{
	cub3d->debug.win.height = HEIGHT;
	cub3d->debug.win.width = WIDTH;
	cub3d->debug.win.win = mlx_new_window(cub3d->mlx.mlx,
		WIDTH, HEIGHT, "cub3d - map");
	cub3d->debug.img.img = mlx_new_image(cub3d->mlx.mlx,
		cub3d->mlx.win.width, cub3d->mlx.win.height);
	cub3d->debug.img.data = mlx_get_mlx_addr(cub3d->debug.img.img,
		&cub3d->debug.img.bits_per_pixel,
		&cub3d->debug.img.size_line, &cub3d->debug.img.endian);
}

static void	init_tex(t_game *cub3d, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub3d->mlx.mlx, path,
		&tex->size_line, &tex->line_count);
	if (tex->img == NULL)
		exit(EXIT_FAILURE);
	tex->data = mlx_get_mlx_addr(tex->img, &tex->bits_per_pixel,
		&tex->size_line, &tex->endian);
	//rotate_index(cub3d, tex);
}

void	init_game(t_game *cub3d)
{
	cub3d->mlx.mlx = mlx_init();
	cub3d->mlx.win.height = HEIGHT;
	cub3d->mlx.win.width = WIDTH;
	cub3d->mlx.win.win = mlx_new_window(cub3d->mlx.mlx,
		WIDTH, HEIGHT, "cub3d - game");
	cub3d->mlx.img.img = mlx_new_image(cub3d->mlx.mlx,
		cub3d->mlx.win.width, cub3d->mlx.win.height);
	cub3d->mlx.img.data = mlx_get_mlx_addr(cub3d->mlx.img.img,
		&cub3d->mlx.img.bits_per_pixel,
		&cub3d->mlx.img.size_line, &cub3d->mlx.img.endian);
	init_tex(cub3d, &cub3d->tex_south, "textures/BrickFireRed.xpm");
	init_debug(cub3d);
	init_player(cub3d);
	init_map(cub3d);
	mlx_do_key_autorepeaton(cub3d->mlx.mlx);
}
