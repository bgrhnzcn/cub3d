#include "cub3d.h"

int	check_same(char *str, char *str2)
{
	if (ft_strncmp(str,str2, ft_strlen(str)) == 0
	&& ft_strncmp(str,str2, ft_strlen(str2)) == 0)
		return (0);
	return (1);
}

int	control_extension(char	*path)
{
	int	i;

	i = ft_strlen(path) - 1;
	if (path[i] == 'b' && path[i - 1] == 'u' && path[i - 2] == 'c'
		&& path[i - 3] == '.' && path[i - 4] && path[i - 4] != '/')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	check_for_spaces(char **line, t_game *cub3d, int i, int j)
{
	char	*res;

	res = malloc(sizeof(char) * (cub3d->map.size.x + 1));
	if (!res)
		perror("Malloc!\n");
	while ((*line)[i])
	{
		if ((*line)[i] == '\t')
		{
			res[j++] = 'X';
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
		if ((!ft_strncmp(sub, "NO", ft_strlen(sub)) && cub3d->parse.no_pth)
			|| (!ft_strncmp(sub, "SO", ft_strlen(sub)) && cub3d->parse.so_pth)
			|| (!ft_strncmp(sub, "WE", ft_strlen(sub)) && cub3d->parse.we_pth)
			|| (!ft_strncmp(sub, "EA", ft_strlen(sub)) && cub3d->parse.ea_pth)
			|| (!ft_strncmp(sub, "F", ft_strlen(sub)) && cub3d->fl_cntrl)
			|| (!ft_strncmp(sub, "C", ft_strlen(sub)) && cub3d->cl_cntrl))
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
