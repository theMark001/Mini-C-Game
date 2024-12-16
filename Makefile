# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long

OBJDIR = obj
MLX_DIR = libs/mlx
LIBFT_DIR = libs/libft
FTPRINTF_DIR = libs/libftprintf

SRC_CHECK = src/check/is_enclosed_in_walls.c src/check/map_check.c
SRC_CORE = src/core/main.c src/core/move_player.c src/core/next_px.c
SRC_MAP = src/map/get_map_info.c src/map/read_and_display_map.c
SRC = $(SRC_CHECK) $(SRC_CORE) $(SRC_MAP)

OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

# Rules of files
all: $(LIBFT_DIR)/libft.a $(FTPRINTF_DIR)/libftprintf.a $(MLX_DIR)/libmlx_Linux.a $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -L$(FTPRINTF_DIR) -L$(MLX_DIR) -lftprintf -lft -lmlx_Linux -lm -lX11 -lXext -o $(NAME)

# Build the object files with dynamic directory creation
$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(FTPRINTF_DIR) -Iinclude -c $< -o $@

# Rules to build the libraries
$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(FTPRINTF_DIR)/libftprintf.a:
	$(MAKE) -C $(FTPRINTF_DIR)

$(MLX_DIR)/libmlx_Linux.a:
	$(MAKE) -C $(MLX_DIR)

# Debug build target
debug: CFLAGS += -g
debug: re

# Rules of actions
.PHONY: all clean fclean re

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FTPRINTF_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FTPRINTF_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all