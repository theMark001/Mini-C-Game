# Vars
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long
SRCDIR = src
OBJDIR = obj
MLX_DIR = mlx
LIBFT_DIR = libft 
SRC = get_map_info.c is_enclosed_in_walls.c main.c map_check.c move_player.c next_px.c read_and_display_map.c
OBJS = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
SRCS = $(addprefix $(SRCDIR)/,$(SRC))

# Rules of files
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lftprintf -framework OpenGL -framework AppKit -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -c $< -o $@

# Rules of actions
.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(OBJDIR)

re: fclean all