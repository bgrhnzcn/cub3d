/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 00:36:56 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/12 00:37:06 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill(char **map, int x, int y, t_game *cub3d)
{
	int	ret;

	ret = 0;
	if (cub3d->map.size.x < 3 || cub3d->map.size.y < 3)
		return (1);
	if (x >= cub3d->map.size.x || y >= cub3d->map.size.y || y < 0 || x < 0)
		return (ret);
	if (map[y][x] == 'X' || map[y][x] == '\0')
	{
		ret = 1;
		return (ret);
	}
	if (map[y][x] == '1')
		return (ret);
	map[y][x] = '1';
	ret += flood_fill(map, x, y + 1, cub3d);
	ret += flood_fill(map, x, y - 1, cub3d);
	ret += flood_fill(map, x + 1, y, cub3d);
	ret += flood_fill(map, x - 1, y, cub3d);
	return (ret);
}

int	check_for_char(char **map, int i, int j, int *control)
{
	while (map[i][++j])
	{
		if (ft_strchr("WSNE", map[i][j]) != NULL)
		{
			if (*control == false)
				*control = true;
			else
				return (printf("There is no WSNE character or there are too many \
of them!\n"), EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	check_for_row(char **map)
{
	int	control;
	int	i;

	i = -1;
	control = false;
	while (map[++i])
		if (check_for_char(map, i, -1, &control) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (control == false)
		return (printf("There is no WSNE character or there are too many of \
them!\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	control_map(t_game	*cub3d, char	**map)
{
	char	**cpy;

	cpy = copy_map(map);
	take_player_pos(cub3d, map);
	cub3d->map.size.y = take_map_size(map);
	if (check_for_row(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cub3d->parse.retval = 0;
	cub3d->parse.retval += flood_fill(cpy, (cub3d->player.pos.x - 0.5),
			(cub3d->player.pos.y - 0.5), cub3d);
	free_dpointer(cpy);
	if (cub3d->parse.retval != EXIT_SUCCESS)
	{
		printf("There is a hole in map.\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	free_if(void *content)
{
	if (content != NULL)
		free(content);
}
