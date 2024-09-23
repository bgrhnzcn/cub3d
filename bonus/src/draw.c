/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:27:56 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/23 19:53:12 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_cube(t_game *cub3d, t_vec2 pos, t_color color)
{
	int	i;
	int	j;
	const int	scale = 20;

	i = 0;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			ft_put_pixel(&cub3d->mini_map, (pos.x * scale) + i, (pos.y * scale) + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *cub3d)
{
	t_vec2		normalized_pos;
	t_player	player;
	float		radius;
	
	radius = 5;
	player = cub3d->player;
	normalized_pos.x = player.pos.x - (int)player.pos.x;
	normalized_pos.y = player.pos.y - (int)player.pos.y;
	printf("posx: %f, posy: %f\n", normalized_pos.x, normalized_pos.y);
	ft_fill_img(&cub3d->mini_map, g_gray);
	for(int i = 0; i < 2 * radius; i++)
		for(int j = 0; j <  2 * radius; j++)
		{
			if ((i + j) % 2 == 0)
				draw_cube(cub3d, (t_vec2){.x = i, .y = j}, g_red);
			else
				draw_cube(cub3d, (t_vec2){.x = i, .y = + j}, g_green);
		}
}

t_color	calculate_shadow(t_color color, float dist, float factor)
{
	t_color	shadow;
	float	shadow_factor;

	shadow_factor = 1 - (dist / factor);
	shadow.red = color.red * shadow_factor;
	shadow.green = color.green * shadow_factor;
	shadow.blue = color.blue * shadow_factor;
	return (shadow);
}

float	calc_pow4(float x)
{
	return (x * x * x);
}

void	draw_background(t_game *cub3d)
{
	int		i;
	int		j;

	i = 0;
	while (i >= 0 && i < WIDTH)
	{
		j = 0;
		while (j >= 0 && j < HEIGHT)
		{
			if (j <= HEIGHT / 2)
				ft_put_pixel(&cub3d->mlx.img, i, j,
					calculate_shadow(cub3d->ceil,
						calc_pow4(j), calc_pow4(HEIGHT / 2)));
			else
				ft_put_pixel(&cub3d->mlx.img, i, j,
					calculate_shadow(cub3d->floor, calc_pow4(HEIGHT - j),
						calc_pow4(HEIGHT / 2)));
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
		if (tex_y >= drw.tex->width)
			tex_y = drw.tex->width - 1;
		ft_put_pixel(&drw.cub3d->mlx.img, drw.index,
			i + (HEIGHT - drw.line_height) / 2,
			calculate_shadow(data[(int)tex_y], drw.dist, MAX_RAY_LENGHT));
		i++;
	}
}

static void	draw_wall_piece(t_game *cub3d, float line_height,
	int index, t_face face)
{
	float	pos_x;
	float	pos_y;
	float	dist;

	pos_x = cub3d->collisions[index].pos.x;
	pos_y = cub3d->collisions[index].pos.y;
	dist = ft_vec2_dist(cub3d->collisions[index].pos, cub3d->player.pos);
	if (face == south)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_south,
			.line_height = line_height, .index = index,
			.tex_x = pos_x - (int)pos_x, .dist = dist});
	if (face == west)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_west,
			.line_height = line_height, .index = index,
			.tex_x = pos_y - (int)pos_y, .dist = dist});
	if (face == north)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_north,
			.line_height = line_height, .index = index,
			.tex_x = pos_x - (int)pos_x, .dist = dist});
	if (face == east)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_east,
			.line_height = line_height, .index = index,
			.tex_x = pos_y - (int)pos_y, .dist = dist});
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
