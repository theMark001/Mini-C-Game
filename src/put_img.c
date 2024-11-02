#include "../mini_game.h"

void read_and_display_map(t_vars *vars, const char *map_path) {
  int fd = open(map_path, O_RDONLY);
  char buffer;
  int x = 0;
  int y = 0;

  while (read(fd, &buffer, 1) > 0) {
    if (buffer == '0') {
      mlx_put_image_to_window(vars->graphics.mlx, vars->graphics.win, vars->graphics.bg_img, x * vars->state.tile_size, y * vars->state.tile_size);
      x++;
    } 
		else if (buffer == 'P') {
      if (!vars->state.initial_position_set) {
        vars->state.current_x = x * vars->state.tile_size;
        vars->state.current_y = y * vars->state.tile_size;
        vars->state.initial_position_set = 1;
      }
      mlx_put_image_to_window(vars->graphics.mlx, vars->graphics.win, vars->graphics.player_img, vars->state.current_x, vars->state.current_y);
      x++;
    } 
		else if (buffer == '\n') {
      y++;
      x = 0;
    }
  }
}