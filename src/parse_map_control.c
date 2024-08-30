#include "cub3d.h"

int	check_first_and_last_line(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
		;
	i -= 1;
	j = -1;
	while (map[0] && map[0][++j])
		if (map[0][j] != 'X' && map[0][j] != '1')
			return (EXIT_FAILURE);
	j = -1;
	while (map[i] && map[i][++j])
		if (map[i][j] != 'X' && map[i][j] != '1')
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_first_and_last_index(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][find_first_one(map[i])] != '1'
			|| map[i][find_last_one(map[i])] != '1')
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	check_for_map_borders(char **map)
{
	if (check_first_and_last_line(map) == EXIT_FAILURE)
	{
		printf("First or last line is not closed!\n");
		return (EXIT_FAILURE);
	}
	if (check_first_and_last_index(map) == EXIT_FAILURE)
	{
		printf("First or last index is not closed!\n");
		return (EXIT_FAILURE);
	}
	if (check_no_wall_situation(map) == EXIT_FAILURE)
	{
		printf("No Wall!!\n");
		return (EXIT_FAILURE);
	}
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
	(void)cub3d;
    if (check_for_char(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_for_map_borders(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_for_undefined_char(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}