#ifndef MINI_GAME_H
#define MINI_GAME_H

#include <mlx.h>
#include <stdio.h>

#define KEY_W 13 // Key code for W on macOS
#define KEY_A 0  // Key code for A on macOS
#define KEY_S 1  // Key code for S on macOS
#define KEY_D 2  // Key code for D on macOS

typedef struct s_vars {
  void *mlx;
  void *win;
  void *player_img; // Player image
  int current_x;    // Current x-position of the player
  int current_y;    // Current y-position of the player 
} t_vars;

















#endif