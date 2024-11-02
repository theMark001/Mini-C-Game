#include "../mini_game.h"

my_map_size map_size(char *map_path) {
  const char *filename = map_path;
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  int first_line_char_count = 0;
  int line_count = 0;
  ssize_t bytes_read;
  char *buffer = (char *)malloc(1024);
  if (!buffer) {
    perror("Memory allocation failed");
    close(fd);
    exit(EXIT_FAILURE);
  }

  int is_first_line = 1;
  while ((bytes_read = read(fd, buffer, 1024)) > 0) {
    for (ssize_t i = 0; i < bytes_read; i++) {
      if (buffer[i] == '\n') {
        line_count++;  // Increment line count at each newline
        if (is_first_line) {
          is_first_line = 0;  // End of first line reached
        }
      } else if (is_first_line) {
        first_line_char_count++;  // Count characters in the first line
      }
    }
  }

  if (bytes_read == -1) {
    perror("Error reading file");
    free(buffer);
    close(fd);
    exit(EXIT_FAILURE);
  }

  // If the last line doesn't end with a newline, count it as a line
  if (bytes_read > 0 && buffer[bytes_read - 1] != '\n') {
    line_count++;
  }

  free(buffer);
  if (close(fd) == -1) {
    perror("Error closing file");
    exit(EXIT_FAILURE);
  }

	int map_width = first_line_char_count * 50;
	int map_height = (line_count + 1) * 50;

  my_map_size output;
  output.width = map_width;
  output.height = map_height;
  return output;
}

// int main() {
//   my_map_size size = map_size("../maps/map.ber");
//   printf("Width: %d\nHeight: %d\n", size.width, size.height);
//   return 0;
// }