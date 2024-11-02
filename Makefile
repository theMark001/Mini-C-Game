# Compiler and flags
CC = gcc
CFLAGS = 

# Directories
MLX_DIR = mlx
SRC_DIR = src

# Source files
SRC = $(SRC_DIR)/mini_game.c $(SRC_DIR)/win_size.c 
OBJ = $(SRC:.c=.o)

# Target executable name
NAME = mini_game

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@  # <- This line must have a tab before $(CC)


$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# Clean up object files and executable
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re