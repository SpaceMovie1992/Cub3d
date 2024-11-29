NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./inc
MLXFLAGS = -lm -lglfw -lpthread

LIBFT = ./Libft/libft.a
MLX = ./MLX42/build/libmlx42.a

BINDIR = bin

SRCS = src/main.c
OBJS = $(SRCS:%.c=$(BINDIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS)
	@echo $(GREEN)"Building $(NAME)"$(DEFAULT);

$(BINDIR);
	@mkdir -p $(BINDIR)

$(MLX):
$(MLX):
	@if [ ! -d "MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git && \
		cd MLX42 && git checkout tags/v2.3.4 && cmake -B build && cmake --build build -j4; \
	fi

$(BINDIR)/%.o: %.c | $(BINDIR)
	@mkdir -p $(dir $@)  # Ensure any needed subdirectories are created
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@if [ ! -d "libft" ]; then \
		echo "Cloning libft..."; \
		git clone git@github.com:ygalsk/libft.git libft && \
		git submodule update --init --recursive && \
		make -C libft; \
	else \
		make -C libft; \
	fi

clean:
	@rm -rf $(BINDIR)
	@make -C libft clean
	@echo $(RED)"Removing $(NAME) object files"$(DEFAULT);

fclean: clean
	@rm -f $(NAME)
	@rm -rf MLX42
	@make -C libft fclean
	@echo $(RED)"Removing $(NAME) and MLX42"$(DEFAULT);

re: fclean all
	@echo $(GREEN)"Rebuilding everything"$(DEFAULT);

.PHONY: all clean fclean re

# Colors
DEFAULT = "\033[39m"
GREEN = "\033[32m"
RED = "\033[31m"
