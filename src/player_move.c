#include "../mini_game.h"

char next_px(int next_x, int next_y, const char *map_path, int tile_size)
{
  // Convert pixel coordinates to tile indices
  int tile_x = next_x / tile_size;
  int tile_y = next_y / tile_size;
  
  // Open the map file
  int fd = open(map_path, O_RDONLY);
  if (fd < 0) {
    perror("Error opening map file");
    return '\0'; // Return null character to indicate an error
  }

  char buffer;
  int current_x = 0, current_y = 0;

  // Read through the file to find the target tile
  while (read(fd, &buffer, 1) == 1) {
    if (buffer == '\n') {
      current_y++;
      current_x = 0;
    } else {
      if (current_x == tile_x && current_y == tile_y) {
        close(fd);
        return buffer; // Return the character found at this position
      }
      current_x++;
    }
  }

  close(fd);
  return '\0'; // Return null character if position not found in the file
}

int move_player(int key, t_vars *vars)
{
  int next_x = vars->state.current_x;
  int next_y = vars->state.current_y;

  // Determine the next position based on key input
  if (key == KEY_W) {
    next_y -= vars->state.tile_size;
  } else if (key == KEY_A) {
    next_x -= vars->state.tile_size;
  } else if (key == KEY_S) {
    next_y += vars->state.tile_size;
  } else if (key == KEY_D) {
    next_x += vars->state.tile_size;
  } else {
    return 0;
  }

  // Check the next position's tile type
  char tile = next_px(next_x, next_y, "maps/map.ber", vars->state.tile_size);

  if (tile == '1') {
    return 0;
  } else if (tile == 'C') {
    // Check if collectible is already saved
    int already_saved = 0;
    for (int i = 0; i < vars->state.collectible_count; i++) {
      if (vars->state.collectible_x[i] == next_x && vars->state.collectible_y[i] == next_y) {
        already_saved = 1;
        break;
      }
    }

    // If not saved, store the collectible position
    if (!already_saved && vars->state.collectible_count < MAX_COLLECTIBLES) {
      vars->state.collectible_x[vars->state.collectible_count] = next_x;
      vars->state.collectible_y[vars->state.collectible_count] = next_y;
      vars->state.collectible_count++;
      printf("Collectible found at (%d, %d)\n", next_x, next_y);
    }
  } else if (tile == 'D') {
    printf("You encountered a door!\n");
  } else if (tile == 'E') {
    printf("You reached the exit!\n");
  }

  // If it's not a wall, update the player's position
  vars->state.current_x = next_x;
  vars->state.current_y = next_y;

  // Update the display
  mlx_clear_window(vars->graphics.mlx, vars->graphics.win);
  read_and_display_map(vars, "maps/map.ber");

  // Display all collectibles
  for (int i = 0; i < vars->state.collectible_count; i++) {
    mlx_put_image_to_window(vars->graphics.mlx, vars->graphics.win, vars->graphics.bg_img, vars->state.collectible_x[i], vars->state.collectible_y[i]);
    printf("Displayed at %d, %d\n", vars->state.collectible_x[i], vars->state.collectible_y[i]);
  }

  // Display player at current position
  mlx_put_image_to_window(vars->graphics.mlx, vars->graphics.win, vars->graphics.player_img, vars->state.current_x, vars->state.current_y);

  return 0;
}
