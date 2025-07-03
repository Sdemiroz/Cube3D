# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/20 13:23:57 by pamatya           #+#    #+#              #
#    Updated: 2025/07/03 02:03:28 by pamatya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	cube3d
NAME_TEST		:=	tests.out
.DEFAULT_GOAL	:=	all
CC				:=	cc
RM				:=	rm -f
RMR				:=	rm -rf

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

LIB_DIR			:=	lib
OBJ_DIR			:=	obj
LIBFT			:=	$(LIB_DIR)/libft.a

INC_DIRS		:=	inc includes lib/includes lib/MLX42/include/MLX42
SRC_DIRS		:=	src_fractals

MLX_DIR			:=	$(LIB_DIR)/MLX42
MLX				:=	$(MLX_DIR)/build/libmlx42.a

################################################################################
###############                     FLAGS                         ##############
################################################################################

# Compiler flags
CFLAGS			:=	-Wall -Werror -Wextra

# For graphics in macOS
MINILIBX		:=	-L/opt/homebrew/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit
# For Linux
# MINILIBX		:=	-lglfw -ldl -pthread -lm

# Linker flags (for libft.a, libmlx42.a and the math library)
LDFLAGS			:=	-L$(LIB_DIR) -lft -L$(MLX_DIR)/build -lmlx42 -lm $(MINILIBX)

ALL_FLAGS		:=	$(CFLAGS) $(LDFLAGS)

# For debugging
DEBUG_FLAGS		:=	-fsanitize=address -g

################################################################################
###############            SOURCES and DEPENDENCIES               ##############
################################################################################

# Tell the Makefile where headers and source files are
vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

# SRCS :=  main.c error.c init_game.c
SRCS	:=	./src/main.c ./src/initiations.c ./src/renditions.c \
			./src/boundaries.c ./src/manage_events.c \
			./src/complex_arithmetic.c ./src/iterations.c ./src/utils.c

OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

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
NC				:=	\033[0m # Reset

# ║
# ╔
# ╗
# ╚
# ╝

################################################################################
##########                         COMPILING                         ###########
################################################################################

all: $(LIBFT) $(NAME) banner

$(LIBFT):
	@make -C $(LIB_DIR)

$(NAME): $(MLX) $(OBJS)
	@echo "$(YELLOW)$(BOLD)Compiling...$(NC)"
	@$(CC) $(ALL_FLAGS) $(LIBFT) $(MLX) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)Compilation successful$(NC)"

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	@cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

banner:
	@echo "\n"
	@echo "$(C1)██████╗ ██╗   ██╗ ██████╗   ███████╗ ██████╗	$(NC)"
	@echo "$(C2)██╔═══╝ ██║   ██║ ██╔══██╗  ╚════██║ ██╔══██╗	$(NC)"
	@echo "$(C3)██║     ██║   ██║ ██████╔╝    █████║ ██║  ██║	$(NC)"
	@echo "$(C4)██║     ██║   ██║ ██║══██╗    ╚══██║ ██║  ██║	$(NC)"
	@echo "$(C5)██████╗ ████████║ ██████╔╝  ███████║ ██████╔╝	$(NC)"
	@echo "$(C6)╚═════╝ ╚═══════╝ ╚═════╝   ╚═════╝  ╚════╝		$(NC)"
	@echo "\n"

clean:
	@echo "$(YELLOW)$(BOLD)Cleaning...$(NC)"
	@$(RMR) $(OBJ_DIR)
	@make clean -C $(LIB_DIR)
	@echo "$(RED)$(BOLD)Cleaned object files$(NC)"

fclean: clean
	@$(RM) $(NAME) $(NAME_TEST)
	@make fclean -C $(LIB_DIR)
	@echo "$(RED)$(BOLD)Cleaned executable and object files$(NC)"

re: fclean all

resub: fclean submodule_update all

submodule_update:
	git submodule update --remote --merge

bonus: all


################################################################################
##########                         DEBUGGING                         ###########
################################################################################

san:
	make CFLAGS="$(DEBUG_FLAGS)" LDFLAGS="$(LDFLAGS_SAN)"
	@echo "$(GREEN)$(BOLD)Compilation successful with fsan$(NC)"

re_sub: submodule_rebuild

submodule_rebuild:
	git submodule deinit -f .
	git submodule update --init --recursive

debug: clean
debug: CFLAGS += -DDEBUG
debug: $(NAME)

redebug: fclean debug

test:
	make $(NAME_TEST) MAIN_FILE="$(SRC_TEST_MAIN)" NAME=$(NAME_TEST)

retest: fclean test

-include $(OBJS:%.o=%.d)

.PHONY: all clean fclean re bonus re_sub submodule_rebuild san debug test
