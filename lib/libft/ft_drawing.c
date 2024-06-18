/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:42:40 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/15 12:36:06 by bgrhnzcn         ###   ########.fr       */
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

void	ft_fill_img(t_win *win, t_img *img, t_color color)
{
	int	i;
	int	j;

	i = 0;
	while (i < win->width)
	{
		j = 0;
		while (j < win->height)
		{
			ft_put_pixel(img, i, j, color);
			j++;
		}
		i++;
	}
}
