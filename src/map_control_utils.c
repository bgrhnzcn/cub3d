#include "cub3d.h"

int	check_for_undefined_char(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = find_first_one(map[i]) - 1;
		while (++j <= find_last_one(map[i]))
		{
			if (ft_strchr("10WSNE", map[i][j]) == NULL)
			{
				printf("There is an undefined char in map!\n");
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

int check_up_bottom_line(char **map, int i, int j)
{
    if ((map[i - 1] && map[i - 1][j] &&  map[i - 1][j] == '0')
	|| (map[i + 1] && map[i + 1][j] &&  map[i + 1][j] == '0'))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int check_no_wall_situation(char **map)
{
    int i;
    int j;

    i = -1;
    while (map[++i])
    {
        j = -1;
        while (map[i][++j])
        {
            if (map[i][j] == 'X')
                if (check_up_bottom_line(map, i, j))
					return (EXIT_FAILURE);
        }
    }
	return (EXIT_SUCCESS);
}