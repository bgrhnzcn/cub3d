/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:53:18 by buozcan           #+#    #+#             */
/*   Updated: 2024/06/04 18:53:29 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_mlx	cub3d;

	(void)argc;
	(void)argv;
	cub3d.mlx = mlx_init();
	cub3d.win.height = HEIGHT;
	cub3d.win.width = WIDTH;
	cub3d.win.win = mlx_new_window(cub3d.mlx, WIDTH, HEIGHT, "cub3d");
	cub3d.img.img = mlx_new_image(cub3d.mlx, cub3d.win.width, cub3d.win.height);
	cub3d.img.data = mlx_get_mlx_addr(cub3d.img.img, &cub3d.img.bits_per_pixel,
		&cub3d.img.size_line, &cub3d.img.endian);
	//ft_put_pixel(&cub3d.img, 30, 30, (t_color){.value = RED});
	//mlx_put_image_to_window(cub3d.mlx, cub3d.win.win, cub3d.img.img, cub3d.win.width, cub3d.win.height);
	mlx_loop(cub3d.mlx);
}
