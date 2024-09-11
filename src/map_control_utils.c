/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 00:37:18 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/12 00:37:19 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	take_map_size(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		;
	return (i);
}

char	**copy_map(char **map)
{
	char	**res;
	int		i;

	i = -1;
	res = malloc(sizeof(char *) * (take_map_size(map) + 1));
	while (map[++i])
		res[i] = ft_strdup(map[i]);
	res[i] = NULL;
	return (res);
}

void	take_player_pos(t_game *cub3d, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("WSNE", map[i][j]) != NULL)
			{
				cub3d->player.pos.x = j + 0.5;
				cub3d->player.pos.y = i + 0.5;
				if (map[i][j] == 'S')
					cub3d->player.dir = (t_vec2){.x = 0, .y = 1};
				if (map[i][j] == 'N')
					cub3d->player.dir = (t_vec2){.x = 0, .y = -1};
				if (map[i][j] == 'W')
					cub3d->player.dir = (t_vec2){.x = -1, .y = 0};
				if (map[i][j] == 'E')
					cub3d->player.dir = (t_vec2){.x = 1, .y = 0};
			}
		}
	}
}

int	check_for_undefined_char(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = find_first_one(map[i]) - 1;
		while (++j <= find_last_one(map[i]))
		{
			if (ft_strchr("10WSNE", map[i][j]) == NULL)
			{
				printf("There is an undefined char in map!\n");
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}
