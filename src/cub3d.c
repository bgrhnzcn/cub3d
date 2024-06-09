/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:53:18 by buozcan           #+#    #+#             */
/*   Updated: 2024/06/09 12:40:04 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*mlx_get_mlx_addr(void *img_ptr, int *bits_per_pixel,
	int *size_line, int *endian)
{
	return (mlx_get_data_addr(img_ptr, bits_per_pixel, size_line,
		endian));
}

int	main(int argc, char **argv)
{
	t_game	cub3d;

	(void)argc;
	(void)argv;
	init_player(&cub3d);
	cub3d.mlx.mlx = mlx_init();
	cub3d.mlx.win.height = HEIGHT;
	cub3d.mlx.win.width = WIDTH;
	cub3d.mlx.win.win = mlx_new_window(cub3d.mlx.mlx, WIDTH, HEIGHT, "cub3d");
	cub3d.mlx.img.img = mlx_new_image(cub3d.mlx.mlx, cub3d.mlx.win.width, cub3d.mlx.win.height);
	cub3d.mlx.img.data = mlx_get_mlx_addr(cub3d.mlx.img.img, &cub3d.mlx.img.bits_per_pixel,
		&cub3d.mlx.img.size_line, &cub3d.mlx.img.endian);
	mlx_do_key_autorepeaton(cub3d.mlx.mlx);
	mlx_loop_hook(cub3d.mlx.mlx, update, &cub3d);
	mlx_hook(cub3d.mlx.win.win, 2, 1, key_input, &cub3d);
	mlx_loop(cub3d.mlx.mlx);
}
