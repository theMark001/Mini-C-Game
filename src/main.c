#include <mlx.h>

int main(void) {
  // Setting up MLX
  void *mlx = mlx_init();

  // Setting up Window
  void *win = mlx_new_window(mlx, 500, 500, "Mini Game");

  // Setting up Imgs
  int player_width, player_height;
  void *player_img = mlx_xpm_file_to_image(mlx, "textures/player.xpm", &player_width, &player_height);

  int enemy_width, enemy_height;
  void *enemy_img = mlx_xpm_file_to_image(mlx, "textures/item.xpm", &enemy_width, &enemy_height);

  // Display the images in the window
  mlx_put_image_to_window(mlx, win, player_img, 50, 50);   // Display player image at (50, 50)
  mlx_put_image_to_window(mlx, win, enemy_img, 300, 300);  // Display enemy image at (300, 300)

  // Keep the window open
  mlx_loop(mlx);
}