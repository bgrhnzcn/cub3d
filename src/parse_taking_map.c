#include "cub3d.h"

void	print_line(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		printf("|%c|", str[i]);
	printf("\n");
}

int	take_and_control_map(char	**res, t_game *cub3d)
{
	int	i;

	i = -1;
	take_max_x(res, cub3d);
	while (res[++i])
		check_for_spaces(&res[i], cub3d);
	if (control_map(cub3d, res) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}