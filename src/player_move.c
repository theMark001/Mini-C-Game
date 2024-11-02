#include "../mini_game.h"

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
  mlx_put_image_to_window(vars->graphics.mlx, vars->graphics.win, vars->graphics.player_img, vars->state.current_x, vars->state.current_y);

  return 0;
}