#include <mlx.h>

int main(void)
{
  // Setting up mlx
  void *mlx = mlx_init();

  // Setting up window
  void *win = mlx_new_window(mlx, 500, 500, "Mini Game");

  // Setting up img
  int img_width;
  int img_height;
  void *img = mlx_xpm_file_to_image(mlx, "textures/photo.xpm", &img_width, &img_height);
  mlx_put_image_to_window(mlx, win, img, 0, 0);

  // Loop for project
  mlx_loop(mlx);
}