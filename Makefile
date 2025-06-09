NAME := cube3d
.DEFAULT_GOAL := all
CC := cc
AR := ar
RM := rm -rf

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

LIBFT	:= ./libft/libft.a

OBJ_DIR := _obj

INC_DIRS := Includes \
			libft \
			libft/garbage_collector

SRC_DIRS := src \
			lexer \

MLX_DIR := lib/MLX42
MLX 	:= $(MLX_DIR)/build/libmlx42.a

# For macOS
MLX42FLAGS := -lglfw -framework Cocoa -framework OpenGL -framework IOKit

# For Linux
# MLX42FLAGS := -lglfw -ldl -pthread -lm

# Tell the Makefile where headers and source files are
vpath %.hpp $(INC_DIRS)
vpath %.cpp $(SRC_DIRS)

################################################################################
###############                  SOURCE FILES                     ##############
################################################################################

MAIN_FILE := src/main.c

SRC_FILES := # init_mini.c tests.c signals.c

MELTING_POT :=	$(SRC_REPO) \
				$(SRC_FILES)

SRC_IN_SRC := $(SRC_FILES)
SRCS := $(MAIN_FILE) $(addprefix src/, $(SRC_IN_SRC)) $(LEXER_EXPANDER_REPO) $(PARSING_REPO) $(EXECUTION_REPO) $(BUILT_INS_REPO)

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

################################################################################
########                         COMPILING                      ################
################################################################################

CFLAGS :=	-Wall -Werror -Wextra -Wpedantic -Wshadow -Wno-shadow \
			-Wconversion -Wsign-conversion -g -MMD -MP \
			$(addprefix -I, $(INC_DIRS))

CFLAGS_SAN := $(CFLAGS) -fsanitize=address
LDFLAGS := -lncurses -lreadline
LDFLAGS_SAN := -lncurses -fsanitize=address -lreadline
ARFLAGS := -rcs

# ANSI color codes
GREEN := \033[0;32m
MAGENTA := \033[0;35m
BOLD := \033[1m
NC := \033[0m # Reset

NAME_TEST=tests.out

all: $(LIBFT) $(NAME) banner

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	@cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

$(NAME): $(MLX) $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(MLX) $(MLX42FLAGS) $(LDFLAGS) -o $(NAME) -lm -g
	@echo "$(GREEN)$(BOLD)Successful Compilation$(NC)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make -C ./libft

# ║
# ╗
# ╔

# ╝
# ╚
banner:
	@echo "\n"
	@echo "\033[38;2;255;105;180m██████╗ ██╗   ██╗ ██████╗   ███████╗ ██████╗     						\033[0m"
	@echo "\033[38;2;204;123;195m██╔═══╝ ██║   ██║ ██╔══██╗  ╚════██║ ██╔══██╗     								\033[0m"
	@echo "\033[38;2;153;141;210m██║     ██║   ██║ ██████╔╝    █████║ ██║  ██║     								\033[0m"
	@echo "\033[38;2;102;159;225m██║     ██║   ██║ ██║══██╗    ╚══██║ ██║  ██║   								\033[0m"
	@echo "\033[38;2;51;175;240m██████╗ ████████║ ██████╔╝  ███████║ ██████╔╝    								\033[0m"
	@echo "\033[38;2;0;191;255m╚═════╝ ╚═══════╝ ╚═════╝   ╚═════╝  ╚════╝     								\033[0m"
	@echo "\n"


clean:
	$(RM) $(OBJ_DIR)
	@make clean -C ./libft

fclean: clean
	$(RM) $(NAME) $(NAME_TEST)
	@make fclean -C ./libft
	@echo "$(MAGENTA)$(BOLD)Executable + Object Files cleaned$(NC)"

re: fclean submodule_update all

submodule_update:
	git submodule update --remote --merge

bonus: all

san:
	make CFLAGS="$(CFLAGS_SAN)" LDFLAGS="$(LDFLAGS_SAN)"
	@echo "$(GREEN)$(BOLD)Successful Compilation with fsan$(NC)"

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
