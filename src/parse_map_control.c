#include "cub3d.h"

int	flood_fill(char **map, int x, int y, t_game *cub3d)
{
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	printf("xsize: %d\n", cub3d->map.size.x);
	printf("ysize: %d\n", cub3d->map.size.y);
	if (x >= cub3d->map.size.x || y >= cub3d->map.size.y || y < 0 || x < 0)
		return (EXIT_SUCCESS);
	if (map[y][x] == 'X' || map[y][x] == '\0')
		return (EXIT_FAILURE);
	if (map[y][x] == '1')
		return (EXIT_SUCCESS);
	map[y][x] = '1';
	cub3d->parse.retval += flood_fill(map, x + 1, y, cub3d);
	cub3d->parse.retval += flood_fill(map, x - 1, y, cub3d);
	cub3d->parse.retval += flood_fill(map, x, y + 1, cub3d);
	cub3d->parse.retval += flood_fill(map, x, y - 1, cub3d);
	return (cub3d->parse.retval);
}

int	check_for_map_borders(t_game *cub3d, char **map)
{
	char	**cpy;

	cpy = copy_map(map);
	cub3d->parse.retval = EXIT_SUCCESS;
	cub3d->map.size.y = take_map_size(map);
	if (flood_fill(cpy, ceilf(cub3d->player.pos.y), floorf(cub3d->player.pos.x), cub3d) != EXIT_SUCCESS)
	{
		printf("Map is not closed!\n");
		return (EXIT_FAILURE);
	}
	exit (1);
	return (EXIT_SUCCESS);
}

int check_for_char(char **map)
{
    int control;
    int i;
    int j;

    i = -1;
	control = false;
    while (map[++i])
    {
        j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E'
			|| map[i][j] == 'S')
			{
				if (control == false)
					control = true;
				else
				{
					printf("There is no WSNE character or there are too many of them!\n");
					return (EXIT_FAILURE);
				}
			}
		}
    }
	if (control == false)
	{
		printf("There is no WSNE character or there are too many of them!\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int control_map(t_game  *cub3d, char **map)
{
	take_player_pos(cub3d, map);
    if (check_for_char(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_for_undefined_char(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_for_map_borders(cub3d, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}