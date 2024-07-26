#include "cub3d.h"

int	take_rgb_value(char	*values, t_color *background)
{
	char	**res;
	int		i;

	res = ft_split(values, ',');
	i = -1;
	if (!res)
		return (EXIT_FAILURE);
	while (res[++i])
		;
	if (i != 3)
		return (free_dpointer(res), EXIT_FAILURE);
	if (ft_atoi(res[0]) > 255 || ft_atoi(res[0]) < 0 || ft_atoi(res[1]) > 255
		|| ft_atoi(res[1]) < 0 || ft_atoi(res[2]) > 255
		|| ft_atoi(res[2]) < 0)
		return (EXIT_FAILURE);
	background->red = ft_atoi(res[0]);
	background->green = ft_atoi(res[1]);
	background->blue = ft_atoi(res[2]);
	return (free_dpointer(res), EXIT_SUCCESS);
}

int	check_for_name(char *temp, t_game *cub3d, int i)
{
	char	*t1;
	char	*sub;

	t1 = ft_strtrim(temp, " \t");
	while (t1[i] && t1[i] != ' ' && t1[i] != '\t')
		i++;
	sub = ft_substr(t1, 0, i);
	if (control_names_and_values(sub, cub3d, 1))
		return (free (t1), free (sub), EXIT_FAILURE);
	if (ft_strncmp(sub, "NO", ft_strlen(sub)) == 0 && !cub3d->parse.no_pth)
		cub3d->parse.no_pth = ft_strtrim(t1 + i, " \t");
	else if (ft_strncmp(sub, "SO", ft_strlen(sub)) == 0 && !cub3d->parse.so_pth)
		cub3d->parse.so_pth = ft_strtrim(t1 + i, " \t");
	else if (ft_strncmp(sub, "WE", ft_strlen(sub)) == 0 && !cub3d->parse.we_pth)
		cub3d->parse.we_pth = ft_strtrim(t1 + i, " \t");
	else if (ft_strncmp(sub, "EA", ft_strlen(sub)) == 0 && !cub3d->parse.ea_pth)
		cub3d->parse.ea_pth = ft_strtrim(t1 + i, " \t");
	else if (ft_strncmp(sub, "F", ft_strlen(sub)) == 0 && cub3d->fl_cntrl++)
		return (free (sub), free (t1), take_rgb_value(ft_strtrim(t1 + i, " \t"),
				&cub3d->floor));
	else if (ft_strncmp(sub, "C", ft_strlen(sub)) == 0 && cub3d->cl_cntrl++)
		return (free (sub), free (t1), take_rgb_value(ft_strtrim(t1 + i, " \t"),
				&cub3d->ceil));
	return (free(sub), free (t1), EXIT_SUCCESS);
}

int	take_all_textures_path(char	**temp, t_game *cub3d)
{
	int	i;

	i = -1;
	cub3d->parse.no_pth = NULL;
	cub3d->parse.ea_pth = NULL;
	cub3d->parse.we_pth = NULL;
	cub3d->parse.so_pth = NULL;
	cub3d->fl_cntrl = false;
	cub3d->cl_cntrl = false;
	while (temp[++i])
	{
		if (!control_names_and_values(NULL, cub3d, 0))
			break ;
		if (check_for_name(temp[i], cub3d, 0))
		{
			printf("Parse error!\n");
			exit (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	size_of_map(char ***res, int fd)
{
	char	*temp;
	char	*temp1;
	char	*temp2;

	temp = get_next_line(fd);
	temp1 = get_next_line(fd);
	while (temp1)
	{
		temp2 = ft_strjoin(temp, temp1);
		free (temp);
		free (temp1);
		temp1 = get_next_line(fd);
		temp = temp2;
	}
	*res = ft_split(temp, '\n');
}

int	take_all_things_from_doc(t_game *cub3d)
{
	char	**temp;
	int		fd;

	fd = open(cub3d->parse.map_path, O_RDONLY);
	if (fd == -1)
		return (printf("Can't open '.cub' file!\n"), EXIT_FAILURE);
	size_of_map(&temp, fd);
	if (take_all_textures_path(temp, cub3d))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
