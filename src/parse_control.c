#include "cub3d.h"

void	check_for_spaces(char **line, t_game *cub3d)
{
	char *res;
	int	i;
	int	j;

	res = malloc(sizeof(char) * (cub3d->map.size.x + 1));
	if (!res)
		perror("Malloc!\n");
	i = 0;
	j = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\t')
		{
			res[j++] = 'X';
			res[j++] = 'X';
			res[j++] = 'X';
			i++;
		}
		else
			res[j++] = (*line)[i++];
	}
	while (j < cub3d->map.size.x)
		res[j++] = 'X';
	res[j] = '\0';
	free (*line);
	*line = res;
}

int	control_names_and_values(char *sub, t_game *cub3d, int status)
{
	if (status == 1)
	{
		if ((ft_strncmp(sub, "NO", ft_strlen(sub)) == 0 && cub3d->parse.no_pth)
			|| (ft_strncmp(sub, "SO", ft_strlen(sub)) == 0 && cub3d->parse.so_pth)
			|| (ft_strncmp(sub, "WE", ft_strlen(sub)) == 0 && cub3d->parse.we_pth)
			|| (ft_strncmp(sub, "EA", ft_strlen(sub)) == 0 && cub3d->parse.ea_pth)
			|| (ft_strncmp(sub, "F", ft_strlen(sub)) == 0 && cub3d->fl_cntrl)
			|| (ft_strncmp(sub, "C", ft_strlen(sub)) == 0 && cub3d->cl_cntrl))
			return (EXIT_FAILURE);
	}
	else
	{
		if (cub3d->parse.no_pth && cub3d->parse.so_pth && cub3d->parse.we_pth
			&& cub3d->parse.ea_pth && cub3d->fl_cntrl && cub3d->cl_cntrl)
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
