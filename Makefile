NAME = cub3d

MLX = lib/mlx/libmlx.a

LIBFT = lib/libft/libft.a

GNL = lib/get_next_line/get_next_line.a

CC = @gcc

INCLUDES_LINUX = -I./lib/mlx -I./lib/get_next_line \
	-I./lib/libft -I./inc

INCLUDES_MAC = -I./lib/mlx -I./lib/get_next_line \
	-I./lib/libft -I./inc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address $(DEBUG)

MLX_FLAGS_LINUX = $(GNL) $(LIBFT) $(MLX) -Bdynamic -L/usr/lib/X11 \
	-lXext -lX11 -lm

MLX_FLAGS_MAC = $(MLX) $(LIBFT) $(GNL) -Bdynamic -framework OpenGL \
	-framework AppKit

SRC = src/cub3d.c \
	src/ft_bresenham_line.c \
	src/draw.c \
	src/update.c \
	src/init.c \
	src/controller.c \
	src/raycast.c \
	src/texture.c \
	src/debug.c

UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	MLX_FLAGS = $(MLX_FLAGS_LINUX)
	CFLAGS += $(INCLUDES_LINUX)
else
	MLX_FLAGS = $(MLX_FLAGS_MAC)
	CFLAGS += $(INCLUDES_MAC)
endif

OBJ = $(SRC:.c=.o)

$(NAME): $(MLX) $(LIBFT) $(GNL) $(OBJ)
	@echo "Compiling CUB3D..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_FLAGS)

all: $(NAME)

$(MLX):
	@if [ ! -d "./lib/mlx" ]; then\
		if [ "$(UNAME)" = "Linux" ]; then\
			echo "Downloading MiniLib x For Linux...";\
			curl -s https://cdn.intra.42.fr/document/document/18343/minilibx-linux.tgz -o ./lib/mlx.tgz;\
		else\
			echo "Downloadig MiniLibx For MacOS...";\
			curl -s https://cdn.intra.42.fr/document/document/18344/minilibx_opengl.tgz -o ./lib/mlx.tgz;\
		fi;\
		mkdir ./lib/mlx;\
		tar xvfz ./lib/mlx.tgz --strip 1 -C ./lib/mlx > /dev/null 2> /dev/null;\
		rm ./lib/mlx.tgz;\
	fi;\
	if [ ! -f "./lib/mlx/libmlx.a" ]; then\
		echo "Compiling MiniLibx...";\
		make -C ./lib/mlx > /dev/null 2> /dev/null;\
	fi;

$(LIBFT):
	@echo "Compiling Libft..."
	@cd lib/libft && make USE_MATH=TRUE > /dev/null

$(GNL):
	@echo "Compiling get_next_line..."
	@cd lib/get_next_line && make > /dev/null

fclean: clean
	@rm -f $(NAME)

clean:
	@rm -f src/*.o
	@make -C lib/libft fclean > /dev/null
	@make -C lib/get_next_line fclean > /dev/null
	@if [ -d "./lib/mlx" ]; then\
		make -C ./lib/mlx clean $2 > /dev/null 2> /dev/null;\
	fi
	@echo "All unnecessery files cleared."
re: fclean all

debug:
	@make all DEBUG="-g -D DEBUG=1"

run: all
	./$(NAME)

.PHONY: all re fclean clean lib run
