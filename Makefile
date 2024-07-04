NAME = cub3d

CC = @gcc

INCLUDES_LINUX = -I./lib/linuxmlx -I./lib/get_next_line \
	-I./lib/libft -I./inc

INCLUDES_MAC = -I./lib/macmlx -I./lib/get_next_line \
	-I./lib/libft -I./inc

CFLAGS = -g -w -Wall -Wextra -fsanitize=address -D DEBUG=1

MLX_FLAGS_LINUX = lib/get_next_line/get_next_line.a lib/libft/libft.a \
	lib/linuxmlx/libmlx.a -Bdynamic -L/usr/lib/X11 -lXext -lX11 -lm

MLX_FLAGS_MAC = lib/macmlx/libmlx.a lib/libft/libft.a \
	lib/get_next_line/get_next_line.a -Bdynamic -framework OpenGL \
	-framework AppKit

SRC = src/cub3d.c src/ft_bresenham_line.c src/draw.c src/update.c src/init.c \
	src/controller.c src/raycast.c src/texture.c src/debug.c

UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	MLX_FLAGS = $(MLX_FLAGS_LINUX)
	CFLAGS += $(INCLUDES_LINUX)
	MLX_VERSION = lib/linuxmlx
else
	MLX_FLAGS = $(MLX_FLAGS_MAC)
	CFLAGS += $(INCLUDES_MAC)
	MLX_VERSION = lib/macmlx
endif

OBJ = $(SRC:.c=.o)

$(NAME): lib $(OBJ)
	@echo "Compiling CUB3D..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_FLAGS)

all: $(NAME)

lib:
	@echo "Compiling Libft..."
	@cd lib/libft && make USE_MATH=TRUE &> /dev/null
	@echo "Compiling get_next_line..."
	@cd lib/get_next_line && make &> /dev/null
	@./configure.sh "$(UNAME)"
	@echo "Compiling MiniLibx For MacOS..."
	@cd $(MLX_VERSION) && make &> /dev/null

fclean: clean
	@rm -f $(NAME)

clean:
	@rm -f src/*.o
	@cd lib/libft && make fclean &> /dev/null
	@cd lib/get_next_line && make fclean &> /dev/null
	@cd $(MLX_VERSION) && make clean &> /dev/null
	@echo "All unnecessery files cleared."
re: fclean all

run: re
	./$(NAME)

.PHONY: all re fclean clean lib run
