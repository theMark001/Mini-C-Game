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
      if (!vars->initial_position_set) { // Only set the player's position initially
        vars->current_x = x * vars->tile_size;
        vars->current_y = y * vars->tile_size;
        vars->initial_position_set = 1; // Set the flag to true
      }
      mlx_put_image_to_window(vars->mlx, vars->win, vars->player_img, vars->current_x, vars->current_y);
      x++;
    } else if (buffer == '\n') {
      y++;
      x = 0;
    }
  }

  if (x > 0) {
    y++;
  }

  if (close(fd) == -1) {
    perror("Error closing file");
  }
}

int move_player(int key, t_vars *vars) {
  if (key == KEY_W) {
    vars->current_y -= vars->tile_size;
  } else if (key == KEY_A) {
    vars->current_x -= vars->tile_size;
  } else if (key == KEY_S) {
    vars->current_y += vars->tile_size;
  } else if (key == KEY_D) {
    vars->current_x += vars->tile_size;
  } else {
    return 0;
  }

  mlx_clear_window(vars->mlx, vars->win);
  read_and_display_map(vars, "maps/map.ber");
  mlx_put_image_to_window(vars->mlx, vars->win, vars->player_img, vars->current_x, vars->current_y);

  return 0;
}

int main(void) {
  t_vars vars;
  vars.mlx = mlx_init();
  vars.initial_position_set = 0; // Initialize the position flag to 0

  my_map_size size = map_size("maps/map.ber");
  vars.tile_size = 50;
  int win_width = size.width * vars.tile_size;
  int win_height = size.height * vars.tile_size;
  vars.win = mlx_new_window(vars.mlx, win_width, win_height, "Mini Game");

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

  read_and_display_map(&vars, "maps/map.ber");
  mlx_hook(vars.win, 2, 1L<<0, move_player, &vars);

  mlx_loop(vars.mlx);
  return 0;
}