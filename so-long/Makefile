# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long
SRCDIR = src
OBJDIR = obj
MLX_DIR = minilibx-linux
LIBFT_DIR = libft
SRC = get_map_info.c is_enclosed_in_walls.c main.c map_check.c move_player.c next_px.c read_and_display_map.c
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
SRCS = $(addprefix $(SRCDIR)/, $(SRC))

# Rules of files
$(NAME): $(LIBFT_DIR)/libftprintf.a $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_DIR)/libmlx_Linux.a -L$(LIBFT_DIR) -lftprintf -lm -lX11 -lXext

$(LIBFT_DIR)/libftprintf.a:
	@make -C $(LIBFT_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -c $< -o $@

# Debug build target
debug: CFLAGS += -g
debug: re

# Rules of actions
.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJDIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all
