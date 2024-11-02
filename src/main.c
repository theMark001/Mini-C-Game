#include <mlx.h>
#include <stdio.h>

int main(void)
{
  void *mlx;
  void *win;
  void *img;
  char *relative_path = "./test.xpm";
  int img_width;
  int img_height;

  mlx = mlx_init();
  if (!mlx)
  {
    fprintf(stderr, "Error initializing MiniLibX\n");
    return (1);
  }

  win = mlx_new_window(mlx, 500, 500, "Image Display");
  if (!win)
  {
    fprintf(stderr, "Error creating window\n");
    return (1);
  }

  printf("Loading XPM file from path: %s\n", relative_path);
  img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
  if (!img)
  {
    fprintf(stderr, "Error loading XPM file\n");
    return (1);
  }

  mlx_put_image_to_window(mlx, win, img, 0, 0);
  mlx_loop(mlx);
  return (0);
}