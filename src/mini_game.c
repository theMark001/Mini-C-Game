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
      mlx_put_image_to_window(vars->graphics.mlx, vars->graphics.win, vars->graphics.bg_img, x * vars->state.tile_size, y * vars->state.tile_size);
      x++;
    } else if (buffer == 'P') {
      if (!vars->state.initial_position_set) { // Only set the player's position initially
        vars->state.current_x = x * vars->state.tile_size;
        vars->state.current_y = y * vars->state.tile_size;
        vars->state.initial_position_set = 1; // Set the flag to true
      }
      mlx_put_image_to_window(vars->graphics.mlx, vars->graphics.win, vars->graphics.player_img, vars->state.current_x, vars->state.current_y);
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
    vars->state.current_y -= vars->state.tile_size;
  } else if (key == KEY_A) {
    vars->state.current_x -= vars->state.tile_size;
  } else if (key == KEY_S) {
    vars->state.current_y += vars->state.tile_size;
  } else if (key == KEY_D) {
    vars->state.current_x += vars->state.tile_size;
  } else {
    return 0;
  }

  mlx_clear_window(vars->graphics.mlx, vars->graphics.win);
  read_and_display_map(vars, "maps/map.ber");
  mlx_put_image_to_window(vars->graphics.mlx, vars->graphics.win, vars->graphics.player_img,
                          vars->state.current_x, vars->state.current_y);

  return 0;
}

int main(void) {
  t_vars vars;
  vars.graphics.mlx = mlx_init();
  vars.state.initial_position_set = 0;

  map_size size = calc_map_size("maps/map.ber");
  vars.state.tile_size = 50;
  int win_width = size.width * vars.state.tile_size;
  int win_height = size.height * vars.state.tile_size;
  vars.graphics.win = mlx_new_window(vars.graphics.mlx, win_width, win_height, "Mini Game");

  int img_width, img_height;
  vars.graphics.bg_img = mlx_xpm_file_to_image(vars.graphics.mlx, "textures/bg.xpm", &img_width, &img_height);
  if (!vars.graphics.bg_img) {
    perror("Error loading background image");
    exit(EXIT_FAILURE);
  }
  vars.graphics.player_img = mlx_xpm_file_to_image(vars.graphics.mlx, "textures/player.xpm", &img_width, &img_height);
  if (!vars.graphics.player_img) {
    perror("Error loading player image");
    exit(EXIT_FAILURE);
  }

  read_and_display_map(&vars, "maps/map.ber");
  mlx_hook(vars.graphics.win, 2, 1L<<0, move_player, &vars);

  mlx_loop(vars.graphics.mlx);
  return 0;
}