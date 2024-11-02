/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:21:05 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/11/02 23:50:28 by marksylaiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_game.h"

void	init_start_pos(t_vars *vars)
{
	vars->state.start_pos_x = vars->state.current_x;
	vars->state.start_pos_y = vars->state.current_y;
}

void	put_img(void *img, int x, int y, t_vars *vars)
{
	mlx_put_image_to_window(vars->graphics.mlx, vars->graphics.win, img, x
		* vars->state.tile_size, y * vars->state.tile_size);
}

void	read_and_display_map(t_vars *vars, const char *map_path)
{
	int		fd;
	char	buffer;
	int		x;
	int		y;

	fd = open(map_path, O_RDONLY);
	x = 0;
	y = 0;
	while (read(fd, &buffer, 1) > 0)
	{
		if (buffer == '0')
		{
			put_img(vars->graphics.bg_img, x, y, vars);
			x++;
		}
		else if (buffer == '1')
		{
			put_img(vars->graphics.wall_img, x, y, vars);
			x++;
		}
		else if (buffer == 'C')
		{
			put_img(vars->graphics.item_img, x, y, vars);
			x++;
		}
		else if (buffer == 'E')
		{
			put_img(vars->graphics.exit_img, x, y, vars);
			x++;
		}
		else if (buffer == 'P')
		{
			if (!vars->state.initial_position_set)
			{
				vars->state.current_x = x * vars->state.tile_size;
				vars->state.current_y = y * vars->state.tile_size;
				vars->state.initial_position_set = 1;
				init_start_pos(vars);
			}
			put_img(vars->graphics.player_img, x, y, vars);
			x++;
		}
		else if (buffer == '\n')
		{
			y++;
			x = 0;
		}
	}
}
