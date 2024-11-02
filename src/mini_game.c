#include "../mini_game.h"

int main(void) {
  // Setting up MLX
  t_vars vars;
  vars.graphics.mlx = mlx_init();
  vars.state.initial_position_set = 0;

  // Setting up Window
  map_info size = get_map_info("maps/map.ber");
  vars.state.tile_size = 50;
  int win_width = size.width * vars.state.tile_size;
  int win_height = size.height * vars.state.tile_size;
  vars.graphics.win = mlx_new_window(vars.graphics.mlx, win_width, win_height, "Mini Game");

  // Setting up Imgs
  int img_width, img_height;
  vars.graphics.bg_img = mlx_xpm_file_to_image(vars.graphics.mlx, "textures/bg.xpm", &img_width, &img_height);
  vars.graphics.player_img = mlx_xpm_file_to_image(vars.graphics.mlx, "textures/player.xpm", &img_width, &img_height);
  vars.graphics.exit_img = mlx_xpm_file_to_image(vars.graphics.mlx, "textures/exit.xpm", &img_width, &img_height);
  vars.graphics.item_img = mlx_xpm_file_to_image(vars.graphics.mlx, "textures/item.xpm", &img_width, &img_height);
  vars.graphics.wall_img = mlx_xpm_file_to_image(vars.graphics.mlx, "textures/wall.xpm", &img_width, &img_height);

  // Display Imgs
  read_and_display_map(&vars, "maps/map.ber");

  // Setting up Movements
  mlx_hook(vars.graphics.win, 2, 1L<<0, move_player, &vars);

  mlx_loop(vars.graphics.mlx);
  return 0;
}