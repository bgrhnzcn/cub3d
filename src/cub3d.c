/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:53:18 by buozcan           #+#    #+#             */
/*   Updated: 2024/09/12 00:37:50 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	control_for_path(char **argv)
{
	(void)argv;
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	cub3d;

	if (argc != 2)
		return (printf("hata!\n"), EXIT_FAILURE);
	control_for_path(argv);
	cub3d.parse.map_path = argv[1];
	init_game(&cub3d);
	mlx_hook(cub3d.mlx.win.win,
		KeyPress, (1 << 0), key_press_handler, &cub3d);
	mlx_hook(cub3d.mlx.win.win,
		KeyRelease, (1 << 1), key_release_handler, &cub3d);
	mlx_hook(cub3d.mlx.win.win,
		Destroy, (1 << 17), key_release_handler, &cub3d);
	mlx_loop_hook(cub3d.mlx.mlx, update, &cub3d);
	mlx_loop(cub3d.mlx.mlx);
}
