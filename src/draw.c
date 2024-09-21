/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:27:56 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/16 18:20:18 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_game *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (i >= 0 && i < WIDTH)
	{
		j = 0;
		while (j >= 0 && j < HEIGHT)
		{
			if (j <= HEIGHT / 2)
				ft_put_pixel(&cub3d->mlx.img, i, j, cub3d->ceil);
			else
				ft_put_pixel(&cub3d->mlx.img, i, j, cub3d->floor);
			j++;
		}
		i++;
	}
}

static void	draw_face(struct s_draw_hlpr drw)
{
	int		i;
	float	tex_y;
	float	full_height;
	t_color	*data;

	data = get_tex_data(drw.tex, drw.tex_x);
	draw_tex_helper(&i, &tex_y, &full_height, &drw.line_height);
	while (i < drw.line_height)
	{
		if (full_height > HEIGHT)
			tex_y = get_tex_y(drw.tex, i + ((full_height - HEIGHT) / 2),
					full_height);
		else
			tex_y = get_tex_y(drw.tex, i,
					drw.line_height);
		if (tex_y >= drw.tex->size_line)
			tex_y = drw.tex->size_line - 1;
		ft_put_pixel(&drw.cub3d->mlx.img, drw.index,
			i + (HEIGHT - drw.line_height) / 2,
			data[(int)tex_y]);
		i++;
	}
}

static void	draw_wall_piece(t_game *cub3d, float line_height,
	int index, t_face face)
{
	float	pos_x;
	float	pos_y;

	pos_x = cub3d->collisions[index].pos.x;
	pos_y = cub3d->collisions[index].pos.y;
	if (face == south)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_south,
			.line_height = line_height, .index = index,
			.tex_x = pos_x - (int)pos_x});
	if (face == west)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_west,
			.line_height = line_height, .index = index,
			.tex_x = pos_y - (int)pos_y});
	if (face == north)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_north,
			.line_height = line_height, .index = index,
			.tex_x = pos_x - (int)pos_x});
	if (face == east)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_east,
			.line_height = line_height, .index = index,
			.tex_x = pos_y - (int)pos_y});
}

void	draw_walls(t_game *cub3d)
{
	float	line_height;
	float	ray_len;
	int		i;

	i = 0;
	while (i < WIDTH)
	{
		if (ft_vec2_equ(cub3d->collisions[i].pos, g_vec2_null))
		{
			i++;
			continue ;
		}
		ray_len = ft_vec2_dist(cub3d->collisions[i].pos, cub3d->player.pos);
		line_height = HEIGHT
			/ (ray_len * cos(ft_deg_to_rad(cub3d->coll_deg[i])));
		draw_wall_piece(cub3d, line_height, i, cub3d->collisions[i].face);
		i++;
	}
}
