# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 10:33:01 by bgrhnzcn          #+#    #+#              #
#    Updated: 2024/09/12 00:32:02 by bgrhnzcn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                                                              #
#                                Colors                                        #
#                                                                              #
################################################################################

BAR = "\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#"
SPACES = "                                                                                                 "

# Colors
RESET = \033[0m
BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m

# Bold
BOLD_BLACK = \033[1;30m
BOLD_RED = \033[1;31m
BOLD_GREEN = \033[1;32m
BOLD_YELLOW = \033[1;33m
BOLD_BLUE = \033[1;34m
BOLD_MAGENTA = \033[1;35m
BOLD_CYAN = \033[1;36m
BOLD_WHITE = \033[1;37m

################################################################################
#                                                                              #
#                            Compile Settings                                  #
#                                                                              #
################################################################################

# Executable Name
NAME = cub3d

# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -g -Wall -Wextra -Werror $(DEBUG)

# Make Flags
MAKEFLAGS += --no-print-directory

# Include Directories
INCLUDES = -I$(MLX_DIR) -I$(GNL_DIR) -I$(LIBFT_DIR) -I$(INC)

# Operating System
OS = $(shell uname 2>/dev/null || echo Unknown)

SHELL = /bin/bash

AUTHOR = buozcan
AUTHOR2 = faata

all: header $(NAME)

################################################################################
#                                                                              #
#                              Source Files                                    #
#                                                                              #
################################################################################

# Source Directory
SRC = ./src

# Object Directory
OBJ = ./obj

# Include Directory
INC = ./inc

# Library Directory
LIB_DIR = ./lib

# Source Files
SRCS = $(SRC)/cub3d.c \
	$(SRC)/draw.c \
	$(SRC)/update.c \
	$(SRC)/init.c \
	$(SRC)/controller.c \
	$(SRC)/raycast.c \
	$(SRC)/texture.c \
	$(SRC)/start.c \
	$(SRC)/parse_control.c \
	$(SRC)/parse_utils.c \
	$(SRC)/parse_taking_map.c \
	$(SRC)/parse_map_control.c \
	$(SRC)/map_control_utils.c \

# Object Directory Creation
$(OBJ):
	@mkdir $(OBJ)

# Object Files
OBJS = $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)

# Object Files Compilation
$(OBJ)/%.o: $(SRC)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $^ &&\
	(echo $^ | awk -F "/" '{printf "$(BOLD_GREEN)%-9s $(BOLD_BLUE)%-30s $(BOLD_GREEN)%-4s\n$(RESET)", "Compiling" , $$2, "[OK]"; fflush()}') ||\
	(echo $^ | awk -F "/" '{printf "$(BOLD_RED)%-9s $(BOLD_BLUE)%-30s $(BOLD_RED)%-4s\n$(RESET)", "FAILED" , $$2, "[KO]"; fflush()}'; exit 1)

################################################################################
#                                                                              #
#                              Libft Settings                                  #
#                                                                              #
################################################################################

# Libft Directory
LIBFT_DIR = $(LIB_DIR)/libft

# Libft Library File
LIBFT = $(LIBFT_DIR)/libft.a

# Libft File Count
LIBFT_FILE_COUNT = $(shell find $(LIBFT_DIR) -type f -name "*.c" | wc -l)

# Libft Compilation Command
LIBFT_COMP = awk '{ \
		if ($$1 == "FAIL") { exit 1} \
		else if ($$1 == "gcc"){ printf "$(BOLD_GREEN)%9s $(BOLD_BLUE)%-30s $(BOLD_GREEN)%-4s\r$(RESET)", "Compiling" , $$9, "[OK]" } \
		fflush() }' <(make USE_MATH=TRUE 2>/dev/null || echo "FAIL");\
	if [ $$? -eq 1 ]; then \
		awk 'BEGIN{ printf "$(BOLD_RED)%9s $(BOLD_BLUE)%-14s $(BOLD_RED)%-4s\n$(RESET)", "Libft Compilation Failed!" , NULL, "[KO]" }'; \
		exit 1;\
	else \
		printf "$(BOLD_GREEN)Libft Compilation Successfull!$(RESET)\n";\
	fi

# Libft Compilation
$(LIBFT):
	@printf "$(BOLD_CYAN)Compiling Libft...\n"
	@cd $(LIBFT_DIR) && $(LIBFT_COMP)

################################################################################
#                                                                              #
#                              Get Next Line Settings                          #
#                                                                              #
################################################################################

# Get Next Line Directory
GNL_DIR = $(LIB_DIR)/get_next_line

# Get Next Line Library File
GNL = $(GNL_DIR)/get_next_line.a

# Get Next Line File Count
GNL_FILE_COUNT = $(shell find $(GNL_DIR) -type f -name "*.c" | wc -l)

# Get Next Line Compilation Command
GNL_COMP = awk '{ \
		if ($$1 == "FAIL") { exit 1} \
		else if ($$1 == "gcc") { printf "$(BOLD_GREEN)%9s $(BOLD_BLUE)%-30s $(BOLD_GREEN)%-4s\r$(RESET)", "Compiling" , $$1, "[OK]" } \
		fflush() }' <(make 2>/dev/null || echo "FAIL");\
	if [ $$? -eq 1 ]; then \
		awk 'BEGIN{ printf "$(BOLD_RED)%9s $(BOLD_BLUE)%-14s $(BOLD_RED)%-4s\n$(RESET)", "GNL Compilation Failed!" , NULL, "[KO]" }'; \
		exit 1;\
	else \
		printf "$(BOLD_GREEN)GNL Compilation Successfull!$(RESET)\n";\
	fi

# Get Next Line Compilation
$(GNL):
	@printf "$(BOLD_CYAN)Compiling GNL...\n"
	@cd $(GNL_DIR) && $(GNL_COMP)

################################################################################
#                                                                              #
#                              MiniLibX Settings                               #
#                                                                              #
################################################################################

# MiniLibX Directory
MLX_DIR = $(LIB_DIR)/mlx

# MiniLibX Library File
MLX = $(MLX_DIR)/libmlx.a

# MiniLibX File Count
MLX_FILE_COUNT = $(shell find $(MLX_DIR) -type f -name "*.c" | wc -l)

# MiniLibX Flags
ifeq ($(OS), Linux) # Linux
MLX_FLAGS = -Bdynamic -L/usr/lib/X11 -lXext -lX11 -lm
else ifeq ($(OS), Darwin) # MacOS
MLX_FLAGS = -Bdynamic -framework OpenGL -framework AppKit
endif

# MiniLibX Directory Creation
$(MLX_DIR):
ifeq ($(OS), Linux) # Linux
	@echo "Downloading MiniLib x For Linux..."
	@curl -s https://cdn.intra.42.fr/document/document/18343/minilibx-linux.tgz -o $(MLX_DIR).tgz
else ifeq ($(OS), Darwin) # MacOS
	@echo "Downloadig MiniLibx For MacOS..."
	@curl -s https://cdn.intra.42.fr/document/document/18344/minilibx_opengl.tgz -o $(MLX_DIR).tgz
endif # Common
	@mkdir $(MLX_DIR)
	@tar xvfz $(MLX_DIR).tgz --strip 1 -C $(MLX_DIR) > /dev/null 2> /dev/null
	@rm $(MLX_DIR).tgz

# Get Next Line Compilation Command
MLX_COMP = awk '{ \
		if ($$1 == "FAIL") { exit 1} \
		else if ($$1 == "gcc") { printf "$(BOLD_GREEN)%9s $(BOLD_BLUE)%-30s $(BOLD_GREEN)%-4s\r$(RESET)", "Compiling" , $$5, "[OK]" } \
		fflush() }' <(make 2>/dev/null || echo "FAIL");\
	if [ $$? -eq 1 ]; then \
		awk 'BEGIN{ printf "$(BOLD_RED)%9s $(BOLD_BLUE)%-14s $(BOLD_RED)%-4s\n$(RESET)", "MiniLibX Compilation Failed!" , NULL, "[KO]" }'; \
		exit 1;\
	else \
		printf "$(BOLD_GREEN)MiniLibX Compilation Successfull!$(RESET)\n";\
	fi

# MiniLibX Compilation
$(MLX): $(MLX_DIR)
	@printf "$(BOLD_CYAN)Compiling MiniLibX...\n"
	@cd $(MLX_DIR) && $(MLX_COMP)

################################################################################
#                                                                              #
#                               Main Rules                                     #
#                                                                              #
################################################################################

$(NAME): $(OBJ) $(MLX) $(LIBFT) $(GNL) $(OBJS)
	@printf "$(BOLD_GREEN)Compiling CUB3D...\n"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@ $(MLX) $(LIBFT) $(GNL) $(MLX_FLAGS) \
		&& printf "$(BOLD_GREEN)CUB3D Compilation Successfull!\n$(RESET)" \
		|| printf "$(BOLD_RED)CUB3D Compilation Failed!\n$(RESET)"

fclean: header clean
	@rm -f $(NAME)

clean: header
	@rm -rf $(OBJ)
	@make -C lib/libft fclean > /dev/null
	@make -C lib/get_next_line fclean > /dev/null
	@if [ -d "$(MLX_DIR)" ]; then\
		make -C $(MLX_DIR) clean > /dev/null 2> /dev/null;\
	fi
	@printf "$(BOLD_MAGENTA)All unnecessary files cleared.\n$(RESET)"

re: header fclean all

header:
	@awk 'BEGIN{ \
		printf "$(BOLD_RED)%.*s\n$(RESET)", 60, $(BAR); \
		printf "$(BOLD_RED)#%.*s#\n$(RESET)", 48, $(SPACES); \
		printf "$(BOLD_RED)#%.*s$(NAME)%.*s#\n$(RESET)", (49 - length("$(NAME)")) / 2, $(SPACES), (48 - length("$(NAME)")) / 2, $(SPACES); \
		printf "$(BOLD_RED)#%.*s#\n$(RESET)", 48, $(SPACES); \
		printf "$(BOLD_RED)#%.*sby: $(AUTHOR)%.*s#\n$(RESET)", (48 - length("by: $(AUTHOR)")) / 4 * 3, $(SPACES), (52 - length("by: $(AUTHOR)")) / 4, $(SPACES); \
		printf "$(BOLD_RED)#%.*sby: $(AUTHOR2)%.*s#\n$(RESET)", (48 - length("by: $(AUTHOR)")) / 4 * 3, $(SPACES), (60 - length("by: $(AUTHOR2)")) / 4, $(SPACES); \
		printf "$(BOLD_RED)#%.*s#\n$(RESET)", 48, $(SPACES); \
		printf "$(BOLD_RED)%.*s\n$(RESET)", 60, $(BAR); \
		}'

.PHONY: all re fclean clean run debug header
