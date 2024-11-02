#include "../mini_game.h"

void read_and_display_map(t_vars *vars, const char *map_path) {
  int fd = open(map_path, O_RDONLY);
  if (fd == -1) {
    perror("Error opening map file");
    exit(EXIT_FAILURE);
  }

  char buffer;
  int x = 0;
  int y = 0;

  while (read(fd, &buffer, 1) > 0) {
    if (buffer == '0') {
      mlx_put_image_to_window(vars->mlx, vars->win, vars->bg_img, x * vars->tile_size, y * vars->tile_size);
      x++;
    } else if (buffer == 'P') {
      vars->current_x = x * vars->tile_size;
      vars->current_y = y * vars->tile_size;
      mlx_put_image_to_window(vars->mlx, vars->win, vars->player_img, vars->current_x, vars->current_y);
      x++;
    } else if (buffer == '\n') {
      y++;
      x = 0;
    }
  }

  // If the last line doesn't end with a newline, display it
  if (x > 0) {
    y++;
  }

  if (close(fd) == -1) {
    perror("Error closing file");
  }
}

int move_player(int key, t_vars *vars) {
  // Move player based on key press
  if (key == KEY_W) {
    vars->current_y -= 50; // Move up
  } else if (key == KEY_A) {
    vars->current_x -= 50; // Move left
  } else if (key == KEY_S) {
    vars->current_y += 50; // Move down
  } else if (key == KEY_D) {
    vars->current_x += 50; // Move right
  } else {
    return 0; // If another key is pressed, do nothing
  }

  // Clear the window by redrawing the background
  int bg_width, bg_height;
  void *bg_img = mlx_xpm_file_to_image(vars->mlx, "textures/bg.xpm", &bg_width, &bg_height);
  for (int y = 0; y < 500; y += bg_height) {
    for (int x = 0; x < 500; x += bg_width) {
      mlx_put_image_to_window(vars->mlx, vars->win, bg_img, x, y);
    }
  }

  // Redraw the player at the new position
  mlx_put_image_to_window(vars->mlx, vars->win, vars->player_img, vars->current_x, vars->current_y);

  return 0;
}

int main(void) {
  t_vars vars;
  vars.mlx = mlx_init();

  // Load map dimensions and set up window size
  my_map_size size = map_size("maps/map.ber");
  vars.tile_size = 50;
  int win_width = size.width * vars.tile_size;
  int win_height = size.height * vars.tile_size;
  vars.win = mlx_new_window(vars.mlx, win_width, win_height, "Mini Game");

  // Load images
  int img_width, img_height;
  vars.bg_img = mlx_xpm_file_to_image(vars.mlx, "textures/bg.xpm", &img_width, &img_height);
  if (!vars.bg_img) {
    perror("Error loading background image");
    exit(EXIT_FAILURE);
  }
  vars.player_img = mlx_xpm_file_to_image(vars.mlx, "textures/player.xpm", &img_width, &img_height);
  if (!vars.player_img) {
    perror("Error loading player image");
    exit(EXIT_FAILURE);
  }

  // Display map based on `map.ber`
  read_and_display_map(&vars, "maps/map.ber");
  mlx_hook(vars.win, 2, 1L<<0, move_player, &vars);


  mlx_loop(vars.mlx);
  return 0;
}