/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:21:05 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/11/03 20:39:37 by marksylaiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_game.h"

void	update_map_info(char c, t_vars *vars, int *is_first_line)
{
	if (c == '\n')
	{
		vars->map_info.height++;
		*is_first_line = 0;
	}
	else
	{
		if (*is_first_line)
			vars->map_info.width++;
		if (c == 'C')
			vars->map_info.all_collectible++;
		else if (c == 'E')
			vars->map_info.all_exits++;
		else if (c == 'P')
			vars->map_info.all_players++;
	}
}

void	get_map_info(t_vars *vars)
{
	int		fd;
	ssize_t	bytes_read;
	char	buffer[1024];
	int		is_first_line;

	is_first_line = 1;
	fd = open(vars->path, O_RDONLY);
	if (fd == -1)
	{
		printf("Map file doesn't exist\n");
		exit(0);
	}
	vars->map_info.width = 0;
	vars->map_info.height = 0;
	vars->map_info.all_collectible = 0;
	vars->map_info.all_exits = 0;
	vars->map_info.all_players = 0;
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
	{
		for (ssize_t i = 0; i < bytes_read; i++)
			update_map_info(buffer[i], vars, &is_first_line);
	}
	vars->map_info.height += 1;
	close(fd);
}
