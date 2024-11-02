#include "../mini_game.h"


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

  // Initialize MiniLibX
  vars.mlx = mlx_init();

  // Create a window
  int win_width = 500;
  int win_height = 500;
  vars.win = mlx_new_window(vars.mlx, win_width, win_height, "Mini Game");

  // Load and display background
  int bg_width, bg_height;
  void *bg_img = mlx_xpm_file_to_image(vars.mlx, "textures/bg.xpm", &bg_width, &bg_height);

  for (int y = 0; y < win_height; y += bg_height) {
    for (int x = 0; x < win_width; x += bg_width) {
      mlx_put_image_to_window(vars.mlx, vars.win, bg_img, x, y);
    }
  }

  // Initialize and display the player image
  int player_width, player_height;
  vars.player_img = mlx_xpm_file_to_image(vars.mlx, "textures/player.xpm", &player_width, &player_height);
  vars.current_x = 50; // Starting x-position of the player
  vars.current_y = 50; // Starting y-position of the player
  mlx_put_image_to_window(vars.mlx, vars.win, vars.player_img, vars.current_x, vars.current_y);

  // Set up the key hook for moving the player
  mlx_hook(vars.win, 2, 1L<<0, move_player, &vars);

  // Start the MiniLibX event loop
  mlx_loop(vars.mlx);
}