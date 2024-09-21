/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:53:18 by buozcan           #+#    #+#             */
/*   Updated: 2024/09/16 18:08:09 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	control_for_path(char **argv)
{
	(void)argv;
	return (EXIT_SUCCESS);
}

int	destroy_handler(t_game *param)
{
	terminate_prog(param, EXIT_SUCCESS);
	return (0);
}

static void	clear_parse(t_parse *parse)
{
	if (parse->ea_pth != NULL)
		free(parse->ea_pth);
	if (parse->no_pth != NULL)
		free(parse->no_pth);
	if (parse->so_pth != NULL)
		free(parse->so_pth);
	if (parse->we_pth != NULL)
		free(parse->we_pth);
}

void	terminate_prog(t_game *cub3d, int status)
{
	clear_parse(&cub3d->parse);
	if (cub3d->mlx.img.img != NULL)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->mlx.img.img);
	if (cub3d->mlx.win.win != NULL)
		mlx_destroy_window(cub3d->mlx.mlx, cub3d->mlx.win.win);
	if (cub3d->map.tiles != NULL)
		free(cub3d->map.tiles);
	if (cub3d->tex_east.img != NULL)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->tex_east.img);
	if (cub3d->tex_north.img != NULL)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->tex_north.img);
	if (cub3d->tex_south.img != NULL)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->tex_south.img);
	if (cub3d->tex_west.img != NULL)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->tex_west.img);
	if (status == EXIT_FAILURE)
		printf("Error!\n");
	exit(status);
}

int	main(int argc, char **argv)
{
	t_game	cub3d;

	cub3d = (t_game){0};
	if (argc != 2)
		return (printf("Error!\n"), EXIT_FAILURE);
	control_for_path(argv);
	cub3d.parse.map_path = argv[1];
	init_game(&cub3d);
	mlx_hook(cub3d.mlx.win.win,
		KeyPress, (1 << 0), key_press_handler, &cub3d);
	mlx_hook(cub3d.mlx.win.win,
		KeyRelease, (1 << 1), key_release_handler, &cub3d);
	mlx_hook(cub3d.mlx.win.win,
		Destroy, (1 << 17), destroy_handler, &cub3d);
	mlx_loop_hook(cub3d.mlx.mlx, update, &cub3d);
	mlx_loop(cub3d.mlx.mlx);
}
