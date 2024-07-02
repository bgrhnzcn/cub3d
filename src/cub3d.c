/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:53:18 by buozcan           #+#    #+#             */
/*   Updated: 2024/07/03 01:15:46 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef __linux__
char	*mlx_get_mlx_addr(void *img_ptr, int *bits_per_pixel,
	int *size_line, int *endian)
{
	return (mlx_get_data_addr(img_ptr, bits_per_pixel, size_line,
		endian));
}
#endif

int	main(int argc, char **argv)
{
	t_game	cub3d;

	(void)argc;
	(void)argv;
	init_game(&cub3d);
	mlx_hook(cub3d.mlx.win.win, KeyPress, (1<<0), key_press_handler, &cub3d);
	mlx_hook(cub3d.mlx.win.win, KeyRelease, (1<<1), key_release_handler, &cub3d);
	mlx_hook(cub3d.mlx.win.win, Destroy, (1<<17), key_release_handler, &cub3d);
	mlx_loop_hook(cub3d.mlx.mlx, update, &cub3d);
	mlx_loop(cub3d.mlx.mlx);
}
