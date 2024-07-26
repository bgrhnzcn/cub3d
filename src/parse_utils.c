#include "cub3d.h"

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