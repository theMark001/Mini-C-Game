# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long
SRCDIR = src
OBJDIR = obj
MLX_DIR = libs/mlx
LIBFT_DIR = libs/libft
FTPRINTF_DIR = libs/libftprintf
SRC = get_map_info.c is_enclosed_in_walls.c main.c map_check.c move_player.c next_px.c read_and_display_map.c
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
SRCS = $(addprefix $(SRCDIR)/, $(SRC))

# Rules of files
all: $(LIBFT_DIR)/libft.a $(FTPRINTF_DIR)/libftprintf.a $(MLX_DIR)/libmlx_Linux.a $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -L$(FTPRINTF_DIR) -L$(MLX_DIR) -lftprintf -lft -lmlx_Linux -lm -lX11 -lXext -o $(NAME)

# Build the object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(FTPRINTF_DIR) -c $< -o $@

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
	rm -rf $(OBJS)
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