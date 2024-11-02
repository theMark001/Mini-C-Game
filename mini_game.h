#ifndef MINI_GAME_H
#define MINI_GAME_H

#include "mlx.h"
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
#define KEY_ESC 53
#define MAX_COLLECTIBLES 100

typedef struct {
  int width;
  int height;
  int all_collectible;
} map_info;

typedef struct {
  int tile_size;
  int current_x;
  int current_y;
  int start_pos_x;
  int start_pos_y;
  int initial_position_set;
  int collectible_count;
  int collectible_x[MAX_COLLECTIBLES];
  int collectible_y[MAX_COLLECTIBLES];
} t_game_state;

typedef struct {
  void *mlx;
  void *win;
  void *bg_img;
  void *player_img;
	void *exit_img;
	void *item_img;
	void *wall_img;
} t_graphics;

typedef struct s_vars {
  t_graphics graphics;
  t_game_state state;
} t_vars;

map_info get_map_info(const char *filename);
void read_and_display_map(t_vars *vars, const char *map_path);
int move_player(int key, t_vars *vars);
int close_window(t_vars *vars);

#endif