#include "cub3d.h"

void	take_max_x(char **res, t_game *cub3d)
{
	int	i;

	i = -1;
	while (res[++i])
		if (take_line_len(res[i]) > cub3d->map.size.x)
			cub3d->map.size.x = take_line_len(res[i]);
}

int	take_line_len(char	*str)
{
	int	len;
	int	i;

	if (!str)
		return (0);
	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] == '\t')
			len += 3;
		else
			len++;
	}
	return (len);
	
}

void	free_dpointer(char	**arr)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
		free (arr[i]);
	free (arr);
}