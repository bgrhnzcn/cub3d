NAME = cub3d

CC = gcc

SRC = src

OBJ = obj

SRCS = $(SRC)/cub3d.c \
	$(SRC)/ft_bresenham_line.c \
	$(SRC)/draw.c \
	$(SRC)/update.c \
	$(SRC)/init.c \
	$(SRC)/controller.c \
	$(SRC)/raycast.c \
	$(SRC)/texture.c \
	$(SRC)/debug.c \
	$(SRC)/start.c \
	$(SRC)/parse_control.c \


MLX = lib/mlx/libmlx.a

LIBFT = lib/libft/libft.a

GNL = lib/get_next_line/get_next_line.a

INCLUDES = -I./lib/mlx -I./lib/get_next_line \
	-I./lib/libft -I./inc

CFLAGS = -Wall -Wextra -Werror $(DEBUG)

MLX_FLAGS_LINUX = $(GNL) $(LIBFT) $(MLX) -Bdynamic -L/usr/lib/X11 \
	-lXext -lX11 -lm

MLX_FLAGS_MAC = $(GNL) $(LIBFT) $(MLX) -Bdynamic -framework OpenGL \
	-framework AppKit

UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	MLX_FLAGS = $(MLX_FLAGS_LINUX)
else
	MLX_FLAGS = $(MLX_FLAGS_MAC)
endif

OBJS = $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)

all: $(NAME)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $?

$(NAME): $(OBJS) $(MLX) $(LIBFT) $(GNL)
	@echo "Compiling CUB3D..."
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(MLX_FLAGS)

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
	@rm -f $(OBJ)/*.o
	@make -C lib/libft fclean > /dev/null
	@make -C lib/get_next_line fclean > /dev/null
	@if [ -d "./lib/mlx" ]; then\
		make -C ./lib/mlx clean $2 > /dev/null 2> /dev/null;\
	fi
	@echo "All unnecessery files cleared."
re: fclean all

debug:
	@make all DEBUG="-g -fsanitize=address -D DEBUG=1" > /dev/null 2> /dev/null

run: $(NAME)
	./$(NAME)

.PHONY: all re fclean clean run debug
