/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:42:40 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/23 16:16:55 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_pixel(t_img *img, int x, int y, t_color color)
{
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
		img->data[x + (img->width * y)] = color;
}

void	ft_fill_img(t_img *img, t_color color)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->width)
	{
		j = 0;
		while (j < img->height)
		{
			ft_put_pixel(img, i, j, color);
			j++;
		}
		i++;
	}
}
