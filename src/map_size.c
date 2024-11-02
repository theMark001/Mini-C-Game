#include "../mini_game.h"

my_map_size map_size(const char *filename) {
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  my_map_size size = {0, 0};
  ssize_t bytes_read;
  char buffer[1024];
  int is_first_line = 1;

  while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
    for (ssize_t i = 0; i < bytes_read; i++) {
      if (buffer[i] == '\n') {
        size.height++;  // Increment line count at each newline
        is_first_line = 0;
      } else if (is_first_line) {
        size.width++;  // Count characters in the first line
      }
    }
  }

  if (bytes_read == -1) {
    perror("Error reading file");
    close(fd);
    exit(EXIT_FAILURE);
  }
  size.height += 1;
  close(fd);
  printf("Width: %d\nHeight: %d\n", size.width, size.height);
  return size;
}