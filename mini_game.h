#ifndef MINI_GAME_H
#define MINI_GAME_H

#include <mlx.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


#define KEY_W 13 // Key code for W on macOS
#define KEY_A 0  // Key code for A on macOS
#define KEY_S 1  // Key code for S on macOS
#define KEY_D 2  // Key code for D on macOS

typedef struct {
  int width;
  int height;
} my_map_size;

typedef struct s_vars {
  void *mlx;
  void *win;
  void *bg_img;
  void *player_img;
  int tile_size;
  int current_x;
  int current_y;
  int initial_position_set; // Flag to check if the initial position is set
} t_vars;

my_map_size map_size(const char *filename);
void read_and_display_map(t_vars *vars, const char *map_path);

#endif