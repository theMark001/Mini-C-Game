/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:21:05 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/11/03 21:07:58 by marksylaiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_game.h"

int is_rectangular(const char *path)
{
    int fd = open(path, O_RDONLY);
    ssize_t bytes_read;
    char buffer[1024];
    int first_line_length = -1;
    int current_line_length = 0;

    // Read the file character by character
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n') {
                if (first_line_length == -1) {
                    first_line_length = current_line_length;
                } else if (current_line_length != first_line_length) {
                    close(fd);
                    return 0;
                }
                current_line_length = 0;  // Reset for the next line
            } else {
                current_line_length++;
            }
        }
    }

    // Handle the last line if it doesn't end with a newline
    if (current_line_length != 0 && current_line_length != first_line_length) {
        close(fd);
        return 0;
    }

    close(fd);
    return 1;
}

int is_enclosed_in_walls(const char *path)
{
    int fd = open(path, O_RDONLY);
    ssize_t bytes_read;
    char buffer[1024];
    int line_length = -1;
    int is_first_line = 1;
    int is_last_line = 0;

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        char *line_start = buffer;

        for (ssize_t i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n' || buffer[i] == '\0') {
                int current_line_length = &buffer[i] - line_start;

                // Set the line length based on the first line
                if (line_length == -1) {
                    line_length = current_line_length;
                }

                // Check the first and last line entirely for '1's
                if (is_first_line || is_last_line) {
                    for (int j = 0; j < current_line_length; j++) {
                        if (line_start[j] != '1') {
                            close(fd);
                            return 0;
                        }
                    }
                } else {  // For middle lines, only check first and last characters
                    if (line_start[0] != '1' || line_start[current_line_length - 1] != '1') {
                        close(fd);
                        return 0;
                    }
                }

                // Set up for the next line
                line_start = &buffer[i + 1];
                is_first_line = 0;
                is_last_line = (buffer[i + 1] == '\0');
            }
        }
    }

    close(fd);
    return 1; // Return 1 for success if all checks pass
}

int map_check(t_vars *vars)
{
    if (vars->map_info.all_players != 1) {
        printf("Error: map should contain exactly one player.\n");
        return 1;
    } else if (vars->map_info.all_exits != 1) {
        printf("Error: map should contain exactly one exit.\n");
        return 1;
    } else if (vars->map_info.all_collectible < 1) {
        printf("Error: map should contain at least one collectible.\n");
        return 1;
    }
 		else if (is_rectangular(vars->path) != 1) {
			printf("Error: map is not rectangular.\n");
			return 1;
		}
		else if (!is_enclosed_in_walls(vars->path)) {
				printf("Error: map is not enclosed in walls.\n");
				return 1;
		}
		return 0;
}
