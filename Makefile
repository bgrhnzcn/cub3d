INCLUDES_LINUX = -I./libs/libft -I./libs/get_next_line \
	-I./libs/linuxmlx -I./includes

INCLUDES_MAC = -I./libs/libft -I./libs/get_next_line \
	-I./libs/macmlx -I./includes

NAME = cub3d

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

MLX_FLAGS_LINUX = libs/get_next_line/get_next_line.a libs/libft/libft.a \
	libs/linuxmlx/libmlx.a -Bdynamic -L/usr/lib/X11 -lXext -lX11 -lm

MLX_FLAGS_MAC = libs/libft/libft.a libs/get_next_line/get_next_line.a \
	libs/macmlx/libmlx.a -Bdynamic -framework OpenGL \
	-framework AppKit

SRCS = srcs/cub3d.c

ifeq ($(shell uname),Linux)
	MLX_FLAGS = $(MLX_FLAGS_LINUX)
	CFLAGS += $(INCLUDES_LINUX)
else
	MLX_FLAGS = $(MLX_FLAGS_MAC)
	CFLAGS += $(INCLUDES_MAC)
endif

OBJ = $(SRCS:.c=.o)

$(NAME): libs $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_FLAGS)

all: $(NAME)

libs:
	cd libs/libft && make USE_MATH=TRUE && make clean
	cd libs/get_next_line && make && make clean

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf srcs/*.o
	cd libs/libft && make fclean
	cd libs/get_next_line && make fclean

re: fclean all

run: re
	./$(NAME)

.PHONY: all re fclean clean libs run