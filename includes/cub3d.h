#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include "mlx.h"
# include "get_next_line_bonus.h"
# include "libft.h"

# define HEIGHT 600
# define WIDTH 800

typedef struct s_tile_map
{
	char	**tiles;
	int		map_size_x : 10;
	int		map_size_y : 10;
}	t_tile_map;

#endif
