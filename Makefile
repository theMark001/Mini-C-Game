# Compiler and flags
CC = gcc
CFLAGS = 

# Directories
MLX_DIR = mlx
SRC_DIR = src

# Source files
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/read_and_display_map.c  $(SRC_DIR)/move_player.c  $(SRC_DIR)/get_map_info.c $(SRC_DIR)/map_check.c  $(SRC_DIR)/next_px.c $(SRC_DIR)/is_enclosed_in_walls.c 
OBJ = $(SRC:.c=.o)

# Target executable name
NAME = mini_game

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@


$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# Clean up object files and executable
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re