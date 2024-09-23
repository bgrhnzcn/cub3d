/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:36:34 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/23 20:25:26 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_img(void *mlx, t_img *img, int width, int height)
{
	img->img = mlx_new_image(mlx, width, height);
	if (!img->img)
		return (EXIT_FAILURE);
	img->data = (t_color *)mlx_get_data_addr(img->img,
	&img->bits_per_pixel, &img->width, &img->endian);
	if (!img->data)
	{
		mlx_destroy_image(mlx, img->img);
		return (EXIT_FAILURE);
	}
	img->width = width;
	img->height = height;
	return (EXIT_SUCCESS);
}


static void	init_player(t_game *cub3d)
{
	cub3d->player.move_speed = 0.1;
	cub3d->player.camera_speed = 2;
}

static void	init_tex(t_game *cub3d, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub3d->mlx.mlx, path,
			&tex->width, &tex->height);
	if (tex->img == NULL)
	{
		printf("Can't find texture file.\n");
		terminate_prog(cub3d, EXIT_FAILURE);
	}
	tex->data = (t_color *)mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->width, &tex->endian);
	if (tex->data == NULL)
		terminate_prog(cub3d, EXIT_FAILURE);
	tex->width /= (tex->bits_per_pixel / 8);
	rotate_index(tex);
}

void	init_win(t_game *cub3d)
{
	if (cub3d->mlx.mlx == NULL)
		terminate_prog(cub3d, EXIT_FAILURE);
	cub3d->mlx.win.height = HEIGHT;
	cub3d->mlx.win.width = WIDTH;
	cub3d->mlx.win.win = mlx_new_window(cub3d->mlx.mlx,
			WIDTH, HEIGHT, "cub3d - game");
	if (cub3d->mlx.win.win == NULL)
		terminate_prog(cub3d, EXIT_FAILURE);
	if (init_img(cub3d->mlx.mlx, &cub3d->mlx.img, cub3d->mlx.win.width, cub3d->mlx.win.height))
		terminate_prog(cub3d, EXIT_FAILURE);
}

void	init_game(t_game *cub3d)
{
	cub3d->inputs = (t_input){0};
	cub3d->mlx.mlx = mlx_init();
	if (take_all_things_from_doc(cub3d))
		terminate_prog(cub3d, EXIT_FAILURE);
	//DEBUG
	cub3d->floor = g_red;
	cub3d->ceil = g_blue;
	//DEBUG
	init_tex(cub3d, &cub3d->tex_north, cub3d->parse.no_pth);
	init_tex(cub3d, &cub3d->tex_south, cub3d->parse.so_pth);
	init_tex(cub3d, &cub3d->tex_east, cub3d->parse.ea_pth);
	init_tex(cub3d, &cub3d->tex_west, cub3d->parse.we_pth);
	mirror_tex(&cub3d->tex_north);
	mirror_tex(&cub3d->tex_east);
	init_win(cub3d);
	init_player(cub3d);
	if (init_img(cub3d->mlx.mlx, &cub3d->mini_map, WIDTH / 3, WIDTH / 3))
		terminate_prog(cub3d, EXIT_FAILURE);
	ft_fill_img(&cub3d->mini_map, g_black);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win.win,
		cub3d->mlx.img.img, 0, 0);
	mlx_do_key_autorepeatoff(cub3d->mlx.mlx);
}
