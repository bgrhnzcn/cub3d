/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:42:40 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/04 18:23:42 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_pixel(t_img *img, int x, int y, t_color color)
{
	char	*point;

	point = (img->data) + ((img->bits_per_pixel / 8) * x)
		+ (img->size_line * y);
	*(unsigned int *)point = color.value;
}

void	ft_fill_img(t_mlx *data, t_color color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->win.width)
	{
		j = 0;
		while (j < data->win.height)
		{
			ft_put_pixel(&(data->img), i, j, color);
			j++;
		}
		i++;
	}
}
