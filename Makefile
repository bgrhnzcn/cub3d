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
else
	MLX_FLAGS = $(MLX_FLAGS_MAC)
	CFLAGS += $(INCLUDES_MAC)
endif

HAS_MLX = $(shell ./check_mlx.sh)

OBJ = $(SRC:.c=.o)

$(NAME): lib $(OBJ)
	@echo "Compiling CUB3D..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_FLAGS)
	@echo $(HAS_MLX)
	@if [ "$(HAS_MLX)" == "true" ]; then \
		echo "\033[5A\033[53DBuilding CUB3D[####################################]\033[4B"; \
	else \
		echo "\033[8A\033[53DBuilding CUB3D[####################################]\033[7B"; \
	fi

all: $(NAME)

lib:
	@echo "Building CUB3D[------------------------------------]"
	@echo "Compiling Libft..."
	@cd lib/libft && make USE_MATH=TRUE &> /dev/null
	@echo "\033[2A\033[53DBuilding CUB3D[########----------------------------]\033[1B"
	@echo "Compiling get_next_line..."
	@cd lib/get_next_line && make &> /dev/null
	@echo "\033[3A\033[53DBuilding CUB3D[###########-------------------------]\033[2B"
	@./configure.sh "$(UNAME)"

fclean: clean
	@rm -f $(NAME)

clean:
	@rm -f src/*.o
	@cd lib/libft && make fclean &> /dev/null
	@cd lib/get_next_line && make fclean &> /dev/null
	@if [[ "$(UNAME)" == "Linux" ]]; then \
		cd lib/linuxmlx && make clean &> /dev/null; \
	else \
		cd lib/macmlx && make clean &> /dev/null; \
	fi
	@echo "All unnecessery files cleared."
re: fclean all

run: re
	./$(NAME)

.PHONY: all re fclean clean lib run
