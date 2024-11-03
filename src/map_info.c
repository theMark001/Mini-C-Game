/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:21:05 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/11/03 03:46:15 by marksylaiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_game.h"

void get_map_info(const char *filename, t_vars *vars)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)  // Check if file opened successfully
    {
        printf("Map file don't exist \n");
        exit(0);
    }

    // Initialize fields to zero to avoid garbage values
    vars->map_info.width = 0;
    vars->map_info.height = 0;
    vars->map_info.all_collectible = 0;
    vars->map_info.all_exits = 0;
    vars->map_info.all_players = 0;

    ssize_t bytes_read;
    char buffer[1024];
    int is_first_line = 1;

    // Read and parse file
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
    {
        for (ssize_t i = 0; i < bytes_read; i++)
        {
            if (buffer[i] == '\n')
            {
                vars->map_info.height++;
                is_first_line = 0;
            }
            else
            {
                if (is_first_line)
                    vars->map_info.width++;
                if (buffer[i] == 'C')
                    vars->map_info.all_collectible++;
                if (buffer[i] == 'E')
                    vars->map_info.all_exits++;
                if (buffer[i] == 'P')
                    vars->map_info.all_players++;
            }
        }
    }
    
    // Account for the last line if it doesn't end with a newline
    vars->map_info.height += 1;

    // Debug output to verify values
    printf("Height: %d, Width: %d, All collectible: %d, All exits: %d, All players: %d \n", vars->map_info.height, vars->map_info.width, vars->map_info.all_collectible, vars->map_info.all_exits, vars->map_info.all_players);

    close(fd);
}
