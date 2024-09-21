/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:23:37 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/16 17:47:34 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_index(t_img *tex)
{
	int	i;
	int	j;

	i = 0;
	while (i < tex->size_line)
	{
		j = i;
		while (j < tex->line_count)
		{
			ft_swap_int((int *)(&(tex->data[j + (tex->size_line * i)].value)),
				(int *)(&(tex->data[i + (tex->line_count * j)].value)));
			j++;
		}
		i++;
	}
}

void	mirror_tex(t_img *tex)
{
	int	i;
	int	j;

	j = 0;
	while (j < tex->size_line)
	{
		i = 0;
		while (i < tex->line_count / 2)
		{
			ft_swap_int((int *)(&tex->data[j + (i * tex->size_line)].value),
				(int *)(&tex->data[j + ((tex->size_line - i - 1)
						* tex->size_line)].value));
			i++;
		}
		j++;
	}
}

float	get_tex_y(t_img *tex, float i, float height)
{
	return (ft_lerp(ft_normalize(i, 0, height),
			0, tex->size_line));
}

void	draw_tex_helper(int *i, float *tex_y,
	float *full_height, float *line_height)
{
	*i = 0;
	*tex_y = 0;
	*full_height = *line_height;
	if (*line_height > HEIGHT)
		*line_height = HEIGHT;
}

t_color	*get_tex_data(t_img *tex, float tex_x)
{
	return (
		tex->data + ((int)ft_lerp(tex_x, 0, tex->size_line) * tex->size_line));
}
