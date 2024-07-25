#include "cub3d.h"

int	control_names_and_values(char *sub, t_game *cub3d)
{
	if ((ft_strncmp(sub, "NO", ft_strlen(sub)) == 0 && cub3d->north_path)
		|| (ft_strncmp(sub, "SO", ft_strlen(sub)) == 0 && cub3d->south_path)
		|| (ft_strncmp(sub, "WE", ft_strlen(sub)) == 0 && cub3d->west_path)
		|| (ft_strncmp(sub, "EA", ft_strlen(sub)) == 0
			&& cub3d->east_path))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
