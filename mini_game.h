#ifndef MINI_GAME_H
#define MINI_GAME_H

#include <mlx.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2

typedef struct {
  int width;
  int height;
} map_size;

typedef struct {
  int tile_size;
  int current_x;
  int current_y;
  int initial_position_set;
} t_game_state;

typedef struct {
  void *mlx;
  void *win;
  void *bg_img;
  void *player_img;
} t_graphics;

typedef struct s_vars {
  t_graphics graphics;
  t_game_state state;
} t_vars;

map_size calc_map_size(const char *filename);
void read_and_display_map(t_vars *vars, const char *map_path);

#endif