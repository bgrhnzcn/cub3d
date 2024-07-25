#include "cub3d.h"

int	control_names_and_values(char *sub, t_game *cub3d)
{
	if ((ft_strncmp(sub, "NO", ft_strlen(sub)) == 0 && cub3d->parse.no_pth)
		|| (ft_strncmp(sub, "SO", ft_strlen(sub)) == 0 && cub3d->parse.so_pth)
		|| (ft_strncmp(sub, "WE", ft_strlen(sub)) == 0 && cub3d->parse.we_pth)
		|| (ft_strncmp(sub, "EA", ft_strlen(sub)) == 0 && cub3d->parse.ea_pth)
		|| (ft_strncmp(sub, "F", ft_strlen(sub)) == 0 && cub3d->fl_cntrl)
		|| (ft_strncmp(sub, "C", ft_strlen(sub)) == 0 && cub3d->cl_cntrl))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
