NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./inc
MLXFLAGS = -lm -lglfw -lpthread -lstdc++

LIB = ./libraries/libraries.a
MLX = ./MLX42/build/libmlx42.a

BINDIR = bin

SRCS = src/main.c src/parsing/checks.c \
				src/parsing/map_check.c \
				src/parsing/parsing.c \
				src/parsing/utils_map.c \
				src/parsing/utils.c \
				src/parsing/utils_parse.c \
				src/raycasting/raycasting.c \
				src/raycasting/keyshandling.c \
				src/raycasting/drawing.c \
				src/init/init.c \
				src/execution/movement.c \
				src/execution/minimap.c \
				src/execution/wallrender.c \
				src/execution/input_handler.c \
				src/execution/texture.c \
				src/rests/utils.c \
				src/rests/utils1.c \
				src/rests/utils2.c 
OBJS = $(SRCS:%.c=$(BINDIR)/%.o)

all: $(NAME)

$(NAME): $(LIB) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB) $(MLX) $(MLXFLAGS)
	@echo $(GREEN)"Building $(NAME)"$(DEFAULT);

$(BINDIR):
	@mkdir -p $(BINDIR)

$(MLX):
	@if [ ! -d "MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git && \
		cd MLX42 && git checkout tags/v2.3.4 && cmake -B build && cmake --build build -j4; \
	fi

$(BINDIR)/%.o: %.c | $(BINDIR)
	@mkdir -p $(dir $@)  # Ensure any needed subdirectories are created
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	@if [ ! -d "libraries" ]; then \
		echo "Cloning libraries..."; \
		git clone git@github.com:makecy/libraries.git && \
		make -C libraries; \
	else \
		make -C libraries; \
	fi

clean:
	@rm -rf $(BINDIR)
	@make -C libraries clean
	@echo $(RED)"Removing $(NAME) object files"$(DEFAULT);

fclean: clean
	@rm -f $(NAME)
	@rm -rf MLX42
	@rm -rf libraries fclean
	@echo $(RED)"Removing $(NAME) and MLX42"$(DEFAULT);
	@echo $(RED)"Removing libraries"$(DEFAULT);

re: fclean all
	@echo $(GREEN)"Rebuilding everything"$(DEFAULT);

.PHONY: all clean fclean re

# Colors
DEFAULT = "\033[39m"
GREEN = "\033[32m"
RED = "\033[31m"
