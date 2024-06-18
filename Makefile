INCLUDES_LINUX = -I./lib/linuxmlx -I./lib/get_next_line \
	-I./lib/libft -I./inc

INCLUDES_MAC = -I./lib/macmlx -I./lib/get_next_line \
	-I./lib/libft -I./inc

NAME = cub3d

CC = gcc

CFLAGS = -g -Wall -Wextra

MLX_FLAGS_LINUX = lib/get_next_line/get_next_line.a lib/libft/libft.a \
	lib/linuxmlx/libmlx.a -Bdynamic -L/usr/lib/X11 -lXext -lX11 -lm

MLX_FLAGS_MAC = lib/macmlx/libmlx.a lib/libft/libft.a \
	lib/get_next_line/get_next_line.a -Bdynamic -framework OpenGL \
	-framework AppKit

SRC = src/cub3d.c src/ft_bresenham_line.c src/draw.c src/update.c src/init.c \
	src/controller.c src/raycast.c src/texture.c

ifeq ($(shell uname),Linux)
	MLX_FLAGS = $(MLX_FLAGS_LINUX)
	CFLAGS += $(INCLUDES_LINUX)
else
	MLX_FLAGS = $(MLX_FLAGS_MAC)
	CFLAGS += $(INCLUDES_MAC)
endif

OBJ = $(SRC:.c=.o)

$(NAME): lib $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_FLAGS)

all: $(NAME)

lib:
	@cd lib/libft && make USE_MATH=TRUE
	@cd lib/get_next_line && make

fclean: clean
	rm -f $(NAME)

clean:
	rm -f src/*.o
	cd lib/libft && make fclean
	cd lib/get_next_line && make fclean

re: fclean all

run: re
	./$(NAME)

.PHONY: all re fclean clean lib run
