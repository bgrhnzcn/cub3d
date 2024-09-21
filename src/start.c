/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 00:37:33 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/12 00:37:34 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	take_rgb_value(char	*values, t_color *background)
{
	char	**res;
	int		i;

	res = ft_split(values, ',');
	free (values);
	i = -1;
	if (!res)
		return (EXIT_FAILURE);
	while (res[++i])
		;
	if (i != 3)
		return (free_dpointer(res), EXIT_FAILURE);
	if (ft_atoi(res[0]) > 255 || ft_atoi(res[0]) < 0 || ft_atoi(res[1]) > 255
		|| ft_atoi(res[1]) < 0 || ft_atoi(res[2]) > 255
		|| ft_atoi(res[2]) < 0)
		return (free_dpointer(res), EXIT_FAILURE);
	background->red = ft_atoi(res[0]);
	background->green = ft_atoi(res[1]);
	background->blue = ft_atoi(res[2]);
	return (free_dpointer(res), EXIT_SUCCESS);
}

int	check_for_name(char *temp, t_game *cub3d, char *t1, int i)
{
	char	*sub;

	t1 = ft_strtrim(temp, " \t");
	while (t1[i] && t1[i] != ' ' && t1[i] != '\t')
		i++;
	sub = ft_substr(t1, 0, i);
	if (control_names_and_values(sub, cub3d, 1))
		return (free (t1), free (sub), EXIT_FAILURE);
	if (check_same(sub, "NO") == 0 && !cub3d->parse.no_pth)
		cub3d->parse.no_pth = ft_strtrim(t1 + i, " \t");
	else if (check_same(sub, "SO") == 0 && !cub3d->parse.so_pth)
		cub3d->parse.so_pth = ft_strtrim(t1 + i, " \t");
	else if (check_same(sub, "WE") == 0 && !cub3d->parse.we_pth)
		cub3d->parse.we_pth = ft_strtrim(t1 + i, " \t");
	else if (check_same(sub, "EA") == 0 && !cub3d->parse.ea_pth)
		cub3d->parse.ea_pth = ft_strtrim(t1 + i, " \t");
	else if (check_same(sub, "F") == 0 && !cub3d->fl_cntrl++)
		return (free (sub), free (t1), take_rgb_value(ft_strtrim(t1 + i, " \t"),
				&cub3d->floor));
	else if (check_same(sub, "C") == 0 && !cub3d->cl_cntrl++)
		return (free (sub), free (t1), take_rgb_value(ft_strtrim(t1 + i, " \t"),
				&cub3d->ceil));
	else
		return (free(sub), free(t1), EXIT_FAILURE);
	return (free(sub), free (t1), EXIT_SUCCESS);
}

int	take_all_textures_path(char	**temp, t_game *cub3d)
{
	char	*trim;
	int		i;

	i = -1;
	while (temp[++i])
	{
		trim = ft_strtrim(temp[i], " \n\t");
		if (trim[0] == '\0')
		{
			free (trim);
			continue ;
		}
		free (trim);
		if (!control_names_and_values(NULL, cub3d, 0))
			break ;
		if (check_for_name(temp[i], cub3d, NULL, 0))
		{
			printf("You must give one acceptable ");
			printf("value for each information!\n");
			return (EXIT_FAILURE);
		}
	}
	if (take_and_control_map((temp + i), cub3d))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	**turn_map_list2array(t_list *list, int size)
{
	char	**res;
	t_list	*temp;
	int		i;

	res = malloc(size * sizeof(char *));
	if (res == NULL)
		return (NULL);
	temp = list;
	i = 0;
	while (temp != NULL && temp->content != NULL)
	{
		res[i] = ft_strtrim(temp->content, "\n");
		i++;
		temp = temp->next;
	}
	res[i] = NULL;
	ft_lstclear(&list, free_if);
	return (res);
}

int	take_all_things_from_doc(t_game *cub3d)
{
	char	**temp;
	int		fd;

	if (control_extension(cub3d->parse.map_path))
		return (printf("Extension of given file must be '.cub' format\n"));
	fd = open(cub3d->parse.map_path, O_RDONLY);
	if (fd == -1)
		return (printf("Can't open given file!\n"), EXIT_FAILURE);
	size_of_map(&temp, fd);
	close(fd);
	if (temp == NULL || take_map_size(temp) < 3)
		return (printf("Given file must contain at least 3 line\n"));
	if (take_all_textures_path(temp, cub3d))
		return (free_dpointer(temp), EXIT_FAILURE);
	return (free_dpointer(temp), EXIT_SUCCESS);
}
