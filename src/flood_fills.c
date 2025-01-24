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
		return (1);
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

void	flood_fill_ever(char **map, int x, int y, t_game *cub3d)
{
	if (cub3d->map.size.x < 3 || cub3d->map.size.y < 3)
		return ;
	if (x >= cub3d->map.size.x || y >= cub3d->map.size.y || y < 0 || x < 0)
		return ;
	if (map[y][x] == 'X' || map[y][x] == 'Z')
		return ;
	map[y][x] = 'Z';
	flood_fill_ever(map, x, y + 1, cub3d);
	flood_fill_ever(map, x, y - 1, cub3d);
	flood_fill_ever(map, x + 1, y, cub3d);
	flood_fill_ever(map, x - 1, y, cub3d);
}
