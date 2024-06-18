/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:23:37 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/18 14:21:21 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_index(t_game *cub3d, t_img *tex)
{
	int	*data;
	int	i;
	int	j;

	i = 0;
	data = (int *)tex->data;
	while (i < tex->size_line)
	{
		j = 0;
		while (j < tex->line_count)
		{
			ft_swap_int(&data[i + (tex->size_line * j)],
				&data[j + (tex->line_count * i)]);
			j++;
		}
		i++;
	}
}
