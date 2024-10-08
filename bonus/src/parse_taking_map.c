/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_taking_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 00:37:26 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/15 19:55:04 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	convert_to_one(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == 'X')
		{
			line[i] = '1';
		}
	}
}

char	*take_map_in_line(char	**map)
{
	char	*res;
	char	*temp;
	char	*temp2;
	int		i;

	temp = ft_strtrim(map[0], "\n");
	temp2 = ft_strtrim(map[1], "\n");
	res = ft_strjoin(temp, temp2);
	free (temp);
	free (temp2);
	i = 1;
	while (map[++i])
	{
		temp2 = ft_strtrim(map[i], "\n");
		temp = ft_strjoin(res, temp2);
		free (temp2);
		free (res);
		res = temp;
	}
	return (res);
}

int	take_and_control_map(char	**res, t_game *cub3d)
{
	char	**cpy;
	int		i;

	i = -1;
	take_max_x(res, cub3d);
	cpy = copy_map(res);
	while (res[++i])
		check_for_spaces(&res[i], cub3d, 0);
	if (check_for_undefined_char(cpy) || control_map(cub3d, res))
		return (free_dpointer(cpy), EXIT_FAILURE);
	cub3d->map.tiles = take_map_in_line(res);
	convert_to_one(cub3d->map.tiles);
	return (free_dpointer(cpy), EXIT_SUCCESS);
}

void	size_of_map(char ***res, int fd)
{
	t_list	*list;
	char	*temp;

	list = ft_lstnew(NULL);
	temp = get_next_line(fd);
	if (!temp)
	{
		free(list);
		*res = NULL;
		return ;
	}
	list->content = temp;
	while (temp)
	{
		temp = get_next_line(fd);
		ft_lstadd_back(&list, ft_lstnew(temp));
	}
	*res = turn_map_list2array(list, ft_lstsize(list));
}
