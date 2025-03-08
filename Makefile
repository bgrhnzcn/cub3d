# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 10:33:01 by bgrhnzcn          #+#    #+#              #
#    Updated: 2024/12/03 20:06:07 by buozcan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX_LINUX_LINK = https://cdn.intra.42.fr/document/document/31130/minilibx-linux.tgz
TEST_FILE = maps/huge.cub

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
CC = cc

# Compiler Flags
CFLAGS = -g -Wall -Wextra -Werror -O3

# Make Flags
MAKEFLAGS += --no-print-directory

# Include Directories
INCLUDES = -I$(MLX_DIR) -I$(GNL_DIR) -I$(LIBFT_DIR) -I$(INC)

ifeq ($(shell whoami), bgrhnzcn)
DEFINES = -D WIDTH=800 -D HEIGHT=800
else ifeq ($(shell whoami), buozcan)
DEFINES = -D WIDTH=800 -D HEIGHT=800
endif

# Operating System
OS = $(shell uname 2>/dev/null || echo Unknown)

SHELL = /bin/bash

AUTHOR = buozcan
AUTHOR2 = faata

all: $(NAME)

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
	$(SRC)/flood_fills.c \

# Object Directory Creation
$(OBJ):
	@mkdir $(OBJ)

$(LIB_DIR):
	@mkdir $(LIB_DIR)

# Object Files
OBJS = $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)

# Object Files Compilation
$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -o $@ -c $< &&\
	(echo $< | awk -F "/" '{printf "$(BOLD_WHITE)%-9s $(BOLD_BLUE)%-30s $(BOLD_GREEN)%-4s\n$(RESET)", "Compiling" , $$2, "[OK]"; fflush()}') ||\
	(echo $< | awk -F "/" '{printf "$(BOLD_WHITE)%-9s $(BOLD_BLUE)%-30s $(BOLD_RED)%-4s\n$(RESET)", "FAILED" , $$2, "[KO]"; fflush()}'; exit 1)

################################################################################
#                                                                              #
#                              Libft Settings                                  #
#                                                                              #
################################################################################

# Libft Directory
LIBFT_DIR = $(LIB_DIR)/libft

# Libft Library File
LIBFT = $(LIBFT_DIR)/libft.a

# Libft Compilation Command
LIBFT_COMP = awk '{ \
		if ($$1 == "FAIL") { exit 1} \
		else if ($$1 == "gcc"){ printf "\t$(BOLD_WHITE)%9s $(BOLD_CYAN)%-30s $(BOLD_GREEN)%-4s\r$(RESET)", "Compiling" , $$9, "[OK]" } \
		fflush() }' <(USE_MATH=TRUE make  2>/dev/null || echo "FAIL");\
	if [ $$? -eq 1 ]; then \
		awk 'BEGIN{ printf "\t$(BOLD_RED)%9s $(BOLD_CYAN)%-14s $(BOLD_RED)%-4s\n$(RESET)", "Libft Compilation Failed!" , NULL, "[KO]" }'; \
		exit 1;\
	else \
		printf "\t$(BOLD_GREEN)Libft Compilation Successfull!$(RESET)\n";\
	fi

# Libft Directory Creation
$(LIBFT_DIR): | $(LIB_DIR)
	@git clone git@github.com:bgrhnzcn/Libft.git $(LIBFT_DIR) &> /dev/null

# Libft Compilation
$(LIBFT): | $(LIBFT_DIR)
	@printf "$(BOLD_WHITE)Building $(BOLD_YELLOW)Libft$(BOLD_WHITE):\n"
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

# Get Next Line Compilation Command
GNL_COMP = awk '{ \
		if ($$1 == "FAIL") { exit 1} \
		else if ($$1 == "gcc") { printf "\t$(BOLD_GREEN)%9s $(BOLD_BLUE)%-30s $(BOLD_GREEN)%-4s\r$(RESET)", "Compiling" , $$1, "[OK]" } \
		fflush() }' <(make 2>/dev/null || echo "FAIL");\
	if [ $$? -eq 1 ]; then \
		awk 'BEGIN{ printf "\t$(BOLD_RED)%9s $(BOLD_BLUE)%-14s $(BOLD_RED)%-4s\n$(RESET)", "GNL Compilation Failed!" , NULL, "[KO]" }'; \
		exit 1;\
	else \
		printf "\t$(BOLD_GREEN)GNL Compilation Successfull!$(RESET)\n";\
	fi

# Libft Directory Creation
$(GNL_DIR): | $(LIB_DIR)
	@git clone git@github.com:bgrhnzcn/get_next_line.git $(GNL_DIR) &> /dev/null

# Get Next Line Compilation
$(GNL): | $(GNL_DIR)
	@printf "$(BOLD_WHITE)Building $(BOLD_YELLOW)GNL$(BOLD_WHITE):\n"
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

# MiniLibX Flags
ifeq ($(OS), Linux) # Linux
MLX_FLAGS = -Bdynamic -L/usr/lib/X11 -lXext -lX11 -lm
else ifeq ($(OS), Darwin) # MacOS
MLX_FLAGS = -Bdynamic -framework OpenGL -framework AppKit
endif

# MiniLibX Directory Creation
$(MLX_DIR): | $(LIB_DIR)
ifeq ($(OS), Linux) # Linux
	printf "$(BOLD_MAGENTA)Downloading MiniLibX For Linux...\n"
	curl -s $(MLX_LINUX_LINK) -o $(MLX_DIR).tgz
else ifeq ($(OS), Darwin) # MacOS
	printf "$(BOLD_MAGENTA)Downloadig MiniLibX For MacOS...\n"
	curl -s https://cdn.intra.42.fr/document/document/28881/minilibx_opengl.tgz -o $(MLX_DIR).tgz
endif # Common
	@mkdir $(MLX_DIR)
	@tar xvfz $(MLX_DIR).tgz --strip 1 -C $(MLX_DIR) > /dev/null 2> /dev/null
	@rm $(MLX_DIR).tgz

# Get Next Line Compilation Command
MLX_COMP = awk '{ \
		if ($$1 == "FAIL") { exit 1} \
		else if ($$1 == "gcc") { printf "\t$(BOLD_GREEN)%9s $(BOLD_BLUE)%-30s $(BOLD_GREEN)%-4s\r$(RESET)", "Compiling" , $$5, "[OK]" } \
		fflush() }' <(make -j16 2> /dev/null || echo "FAIL");\
	if [ $$? -eq 1 ]; then \
		awk 'BEGIN{ printf "\t$(BOLD_RED)%9s $(BOLD_BLUE)%-14s $(BOLD_RED)%-4s\n$(RESET)", "MiniLibX Compilation Failed!" , NULL, "[KO]" }'; \
		exit 1;\
	else \
		printf "\t$(BOLD_GREEN)MiniLibX Compilation Successfull!$(RESET)\n";\
	fi

# MiniLibX Compilation
$(MLX): | $(MLX_DIR)
	@printf "$(BOLD_WHITE)Building $(BOLD_YELLOW)MiniLibX$(BOLD_WHITE):\n"
	@cd $(MLX_DIR) && $(MLX_COMP)

################################################################################
#                                                                              #
#                               Main Rules                                     #
#                                                                              #
################################################################################

$(NAME): $(MLX) $(LIBFT) $(GNL) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@ $(MLX) $(LIBFT) $(GNL) $(MLX_FLAGS) \
		&& printf "$(BOLD_WHITE)%-9s $(BOLD_CYAN)%-30s $(BOLD_GREEN)%-4s\n$(RESET)" "Linking" "$(NAME)" "[OK]"\
		|| printf "$(BOLD_WHITE)%-9s $(BOLD_CYAN)%-30s $(BOLD_RED)%-4s\n$(RESET)" "Linking" "$(NAME)" "[KO]"

fclean: clean
	@rm -f $(NAME)
	@printf "$(BOLD_MAGENTA)Executable removed.\n$(RESET)"

clean:
	@rm -rf $(OBJ)
	@make -C lib/libft fclean > /dev/null
	@make -C lib/get_next_line fclean > /dev/null
	@if [ -d "$(MLX_DIR)" ]; then\
		make -C $(MLX_DIR) clean > /dev/null 2> /dev/null;\
	fi
	@printf "$(BOLD_MAGENTA)All unnecessary files cleared.\n$(RESET)"

re: fclean all

test: $(NAME)
	@printf "$(BOLD_WHITE)Running $(BOLD_GREEN)$(NAME) $(BOLD_WHITE)with $(BOLD_CYAN)$(TEST_FILE) $(BOLD_WHITE)map...$(RESET)\n"
	@./$(NAME) $(TEST_FILE)
	@xset r on 2> /dev/null

leak: $(NAME)
	@printf "$(BOLD_WHITE)Leak: Running $(BOLD_GREEN)$(NAME) $(BOLD_WHITE)with $(BOLD_CYAN)$(TEST_FILE) $(BOLD_WHITE)map...$(RESET)\n"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(TEST_FILE)
	@xset r on 2> /dev/null

update:
	@printf "$(BOLD_GREEN)Updating Project:\n" && git pull | awk '{printf "$(RESET)\t%s\n", $$0}'
	@printf "$(BOLD_GREEN)Updating Libft:\n" && cd lib/libft && git pull | awk '{printf "$(RESET)\t%s\n", $$0}'
	@printf "$(BOLD_GREEN)Updating Get_Next_Line:\n" && cd lib/get_next_line && git pull | awk '{printf "$(RESET)\t%s\n", $$0}'

credit:
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

help:
	@awk 'BEGIN{ \
		printf "$(BOLD_GREEN)How to use this Makefile:\n"; \
		printf "\t$(BOLD_CYAN)make: $(BOLD_WHITE)Builds the project.\n"; \
		printf "\t$(BOLD_CYAN)make re: $(BOLD_WHITE)Rebuilds the project.\n"; \
		printf "\t$(BOLD_CYAN)make clean: $(BOLD_WHITE)Removes object files.\n"; \
		printf "\t$(BOLD_CYAN)make fclean: $(BOLD_WHITE)Removes object files and executable.\n"; \
		printf "\t$(BOLD_CYAN)make update: $(BOLD_WHITE)Updates the project and dependencies from GitHub.\n"; \
		printf "\t$(BOLD_CYAN)make test: $(BOLD_WHITE)Runs the project with $(TEST_FILE) scene.\n"; \
		printf "\t$(BOLD_CYAN)make leak: $(BOLD_WHITE)Runs the project with $(TEST_FILE) scene and checks for memory leaks.\n"; \
		printf "\t$(BOLD_CYAN)make credit: $(BOLD_WHITE)Shows the project credits.\n"; \
		printf "\t$(BOLD_CYAN)make help: $(BOLD_WHITE)Shows this help message.\n"; \
	}'

.PHONY: all re fclean clean run credit test help
