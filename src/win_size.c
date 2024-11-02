#include "../mini_game.h"

map_size calc_map_size(const char *filename) {
  int fd = open(filename, O_RDONLY);
  map_size size = {0, 0};
  ssize_t bytes_read;
  char buffer[1024];
  int is_first_line = 1;

  while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
    for (ssize_t i = 0; i < bytes_read; i++) {
      if (buffer[i] == '\n') {
        size.height++;
        is_first_line = 0;
      } else if (is_first_line) {
        size.width++;
      }
    }
  }
  size.height += 1;
  close(fd);
  return size;
}