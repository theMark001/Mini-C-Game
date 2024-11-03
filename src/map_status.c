/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 21:50:51 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/11/03 21:50:51 by marksylaiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_game.h"

char	next_px(int next_x, int next_y, t_vars *vars)
{
	int		tile_x;
	int		tile_y;
	int		fd;
	char	buffer;
	int		current_x;
	int		current_y;

	current_x = 0;
	current_y = 0;
	tile_x = next_x / vars->state.tile_size;
	tile_y = next_y / vars->state.tile_size;
	fd = open(vars->path, O_RDONLY);
	while (read(fd, &buffer, 1) == 1)
	{
		if (buffer == '\n')
		{
			current_y++;
			current_x = 0;
		}
		else
		{
			if (current_x == tile_x && current_y == tile_y)
			{
				close(fd);
				return (buffer);
			}
			current_x++;
		}
	}
	close(fd);
	return ('\0');
}

int	close_window(t_vars *vars)
{
	mlx_destroy_window(vars->graphics.mlx, vars->graphics.win);
	exit(0);
	return (0);
}