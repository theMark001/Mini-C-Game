#include <mlx.h>

int main(void)
{
  // Setting up mlx
  void *mlx;
  mlx = mlx_init();

  // Setting up window
  void *win;
  win = mlx_new_window(mlx, 500, 500, "Image Display");


  void *img;
  char *relative_path = "textures/photo.xpm";
  int img_width;
  int img_height;

  img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
  mlx_put_image_to_window(mlx, win, img, 0, 0);

  // Loop for project
  mlx_loop(mlx);
}