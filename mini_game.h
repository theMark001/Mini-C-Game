#ifndef MINI_GAME_H
#define MINI_GAME_H

#include <mlx.h>
#include <stdio.h>

#include <fcntl.h>    // For open
#include <unistd.h>   // For read, close, write
#include <stdlib.h>   // For malloc, free, exit
#include <stdio.h>    // For perror
#include <string.h>   // For strerror
#include <errno.h>    // For errno

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

typedef struct {
  int width;
  int height;
} my_map_size;

my_map_size map_size(char *map_path);














#endif