#include "cub3d.h"

int	flood_fill(char **map, int x, int y, t_game *cub3d)
{
	int	ret;

	ret = 0;
	if (x >= cub3d->map.size.x || y >= cub3d->map.size.y || y < 0 || x < 0)
		return (ret);
	if (map[y][x] == 'X' || map[y][x] == '\0')
	{
		ret = 1;
		return (ret);
	}
	if (map[y][x] == '1')
		return (ret);
	map[y][x] = '1';
	ret += flood_fill(map, x + 1, y, cub3d);
	ret += flood_fill(map, x - 1, y, cub3d);
	ret += flood_fill(map, x, y + 1, cub3d);
	ret += flood_fill(map, x, y - 1, cub3d);
	return (ret);
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
	char	**cpy;

	cpy = copy_map(map);
	take_player_pos(cub3d, map);
	printf("px: %f\n", cub3d->player.pos.x);
	printf("py: %f\n", cub3d->player.pos.y);
	//exit (1);
	cub3d->map.size.y = take_map_size(map);
    if (check_for_char(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_for_undefined_char(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cub3d->parse.retval = 0;
	cub3d->parse.retval += flood_fill(cpy, cub3d->player.pos.y, cub3d->player.pos.x, cub3d);
	free_dpointer(cpy);
	if (cub3d->parse.retval != EXIT_SUCCESS)
	{
		printf("There is a hole in map.\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}