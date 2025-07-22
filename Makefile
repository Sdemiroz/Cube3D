# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/20 13:23:57 by pamatya           #+#    #+#              #
#    Updated: 2025/07/22 20:15:35 by pamatya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	cub3d
NAME_TEST		:=	tests.out
.DEFAULT_GOAL	:=	all
CC				:=	cc
RM				:=	rm -f
RMR				:=	rm -rf

# For verbose output and termporarily ignoring warnings
verb			:=	no
ignore			:=	no

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

LIB_DIR			:=	lib
OBJ_DIR			:=	obj
LIBFT			:=	$(LIB_DIR)/libft.a

INC_DIRS		:=	include lib/includes lib/MLX42/include/MLX42
SRC_DIRS		:=	src

MLX_DIR			:=	$(LIB_DIR)/MLX42
MLX				:=	$(MLX_DIR)/build/libmlx42.a

################################################################################
###############                     FLAGS                         ##############
################################################################################

# Compiler flags for warnings
CFLAGS			:=	-Wall -Werror -Wextra
# Compiler dependency flags for generating dependency (.d) files
DEPFLAGS		:=	-MMD -MP

CFLAGS			+=	$(DEPFLAGS)

# Compiler flags for debugging
DEBUG_FLAGS		:=	-fsanitize=address -g
debug			:=	no

ifeq ($(ignore), yes)
	CFLAGS		=	$(DEPFLAGS)
endif

ifeq ($(debug), yes)
	CFLAGS		+=	$(DEBUG_FLAGS)
endif

# For graphics and window management libraries (for both macOS and Linux)
UNAME_S			:=	$(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	MINILIBX	:=	-lglfw -framework Cocoa -framework OpenGL -framework IOKit
	ifeq ($(USER), pranujamatya)
		MINILIBX	+=	-L/opt/homebrew/lib
	endif
else ifeq ($(UNAME_S), Linux) # Need to confirm these Linux flags for Cub3D
	MINILIBX	:=	-lglfw -ldl
endif

# Linker flags (for libft.a, libmlx42.a and the math library)
LDFLAGS			:=	-L$(LIB_DIR) -lft -L$(MLX_DIR)/build -lmlx42 $(MINILIBX) -lm

ALL_FLAGS		:=	$(CFLAGS) $(LDFLAGS)

################################################################################
###############            SOURCES and DEPENDENCIES               ##############
################################################################################

# Tell the Makefile where headers and source files are
vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

SRCS	:=	main.c \
			spawn.c start.c draw.c renders.c events.c string_utils.c \
			draw_circle.c utils_valids.c\
			error.c init_game.c \
			interims/circles_improved.c \
			tmp_parsing/minimap_parser.c tmp_parsing/print_map_utils.c

OBJS	:=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
DEPS	:=	$(OBJS:%.o=%.d)

# For header changes tracking through dependency files
-include $(DEPS)

################################################################################
##########                          COLORS                           ###########
################################################################################

# ANSI color codes
RED				:=	\033[0;31m
GREEN			:=	\033[0;32m
YELLOW			:=	\033[0;33m
MAGENTA			:=	\033[0;35m
BOLD			:=	\033[1m
C1				:=	\033[38;2;255;105;180m
C2				:=	\033[38;2;204;123;195m
C3				:=	\033[38;2;153;141;210m
C4				:=	\033[38;2;102;159;225m
C5				:=	\033[38;2;51;175;240m
C6				:=	\033[38;2;0;191;255m
NC				:=	\033[0m

# ║
# ╔
# ╗
# ╚
# ╝

################################################################################
##########                        COMPILATION                        ###########
################################################################################

all: verbos $(LIBFT) $(NAME) banner

verbos:
	@if [ "$(verb)" = "yes" ]; then \
		echo "Debug = $(debug)"; \
		echo "Cflags = $(CFLAGS)"; \
		echo "User = $(USER)"; \
		echo "Ldflags = $(LDFLAGS)"; \
		echo "All flags = $(ALL_FLAGS)"; \
	fi
	@if [ ! -f "$(NAME)" ]; then \
		echo "$(YELLOW)$(BOLD)Compiling...$(NC)"; \
	fi

$(LIBFT):
	@echo "$(YELLOW)$(BOLD)Building libft library...$(NC)"
	@make -C $(LIB_DIR)

$(NAME): $(MLX) $(OBJS)
	@$(CC) $(ALL_FLAGS) $(LIBFT) $(MLX) $(OBJS) -o $(NAME)
	@if [ "$(debug)" = "yes" ]; then \
		echo "$(GREEN)$(BOLD)Compilation successful for debugging$(NC)"; \
	else \
		echo "$(GREEN)$(BOLD)Compilation successful$(NC)"; \
	fi

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git submodule add https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	@if [ ! -d "$(MLX_DIR)/build" ]; then \
		echo "$(YELLOW)$(BOLD)Building MLX42 library...$(NC)"; \
	fi
	@cd $(MLX_DIR) && cmake -B build > /dev/null 2>&1 \
	&& cmake --build build -j4 > /dev/null 2>&1

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

banner:
	@echo "\n"
	@echo "$(C1)██████╗ ██╗   ██╗ ██████╗   ███████╗ ██████╗	$(NC)"
	@echo "$(C2)██╔═══╝ ██║   ██║ ██╔══██╗  ╚════██║ ██╔══██╗	$(NC)"
	@echo "$(C3)██║     ██║   ██║ ██████╔╝    █████║ ██║  ██║	$(NC)"
	@echo "$(C4)██║     ██║   ██║ ██║══██╗    ╚══██║ ██║  ██║	$(NC)"
	@echo "$(C5)██████╗ ████████║ ██████╔╝  ███████║ ██████╔╝	$(NC)"
	@echo "$(C6)╚═════╝ ╚═══════╝ ╚═════╝   ╚══════╝ ╚═════╝	$(NC)"
	@echo "\n"

clean:
	@$(RMR) $(OBJ_DIR)
	@make clean -C $(LIB_DIR)
	@echo "$(RED)$(BOLD)Cleaned objects and dependencies$(NC)"

fclean: clean
	@$(RM) $(NAME) $(NAME_TEST)
	@make fclean -C $(LIB_DIR)
	@echo "$(RED)$(BOLD)Cleaned executable$(NC)"

re: fclean all

bonus: all

######## -------------------------------------------------------------- ########
##########                         DEBUGGING                         ###########
######## -------------------------------------------------------------- ########
	
debug:
	@$(MAKE) re debug=yes
	lldb

rebug: fclean debug

######## -------------------------------------------------------------- ########
##########                         SUBMODULE                         ###########
######## -------------------------------------------------------------- ########

resub: fclean submodule_update all

submodule_update:
	@git submodule update --remote --merge
	@echo "$(GREEN)$(BOLD)Sub-module MLX42 updated$(NC)"

rebuild: sub_deinit sub_init
	@echo "$(GREEN)$(BOLD)Sub-module MLX42 rebuilt$(NC)"

sub_deinit:
	@printf "$(RED)" && git submodule deinit -f .

sub_init:
	@printf "$(YELLOW)" && git submodule update --init --recursive
	

######## -------------------------------------------------------------- ########
##########                    TESTING (UNCHANGED)                    ###########
######## -------------------------------------------------------------- ########

test:
	make $(NAME_TEST) MAIN_FILE="$(SRC_TEST_MAIN)" NAME=$(NAME_TEST)

retest: fclean test


# ---------------------------------  PHONY  ---------------------------------- #
.PHONY: all clean fclean re bonus debug rebug resub rebuild test retest
