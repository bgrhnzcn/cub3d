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
		return (EXIT_FAILURE);
}

int	check_for_name(char *temp, t_game *cub3d)
{
	char	*t1;
	char	*sub;
	int		i;


	i = 0;
	t1 = ft_strtrim(temp, " \t");
	while (t1[i] && t1[i] != ' ' && t1[i] != '\t')
		i++;
	sub = ft_substr(t1, 0, i);
	if (ft_strncmp(sub, "NO", ft_strlen(sub)) == 0)
		cub3d->north_path = ft_strtrim(t1 + i, " \t");
	if (ft_strncmp(sub, "SO", ft_strlen(sub)) == 0)
		cub3d->south_path = ft_strtrim(t1 + i, " \t");
	if (ft_strncmp(sub, "WE", ft_strlen(sub)) == 0)
		cub3d->west_path = ft_strtrim(t1 + i, " \t");
	if (ft_strncmp(sub, "EA", ft_strlen(sub)) == 0)
		cub3d->east_path = ft_strtrim(t1 + i, " \t");
	if (ft_strncmp(sub, "F", ft_strlen(sub)) == 0)
		if (take_rgb_value(ft_strtrim(t1 + i, " \t"), &cub3d->floor));
			return (EXIT_FAILURE);
	if (ft_strncmp(sub, "C", ft_strlen(sub)) == 0)
		if (take_rgb_value(ft_strtrim(t1 + i, " \t"), &cub3d->ceil));
			return (EXIT_FAILURE);
	
}

void	take_all_textures_path(char	**temp, t_game *cub3d)
{
	int	i;

	i = -1;
	while (temp[++i])
		if (check_for_name(temp[i], cub3d) == EXIT_FAILURE)
			exit (EXIT_FAILURE);
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

	fd = open(cub3d->map_path, O_RDONLY);
	if (fd == -1)
		return (printf("Can't open '.cub' file!\n"), EXIT_FAILURE);
	size_of_map(&temp, fd);
	take_all_textures_path(temp, cub3d);
	return (EXIT_SUCCESS);

}