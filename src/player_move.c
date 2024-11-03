/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:21:05 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/11/03 21:43:22 by marksylaiev      ###   ########.fr       */
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

int	move_player(int key, t_vars *vars)
{
	int		next_x;
	int		next_y;
	char	tile;
	int		already_saved;
	int		i;

	next_x = vars->state.current_x;
	next_y = vars->state.current_y;
	if (key == KEY_W)
		next_y -= vars->state.tile_size;
	else if (key == KEY_A)
		next_x -= vars->state.tile_size;
	else if (key == KEY_S)
		next_y += vars->state.tile_size;
	else if (key == KEY_D)
		next_x += vars->state.tile_size;
	else if (key == KEY_ESC)
		close_window(vars);
	else
		return (0);
	tile = next_px(next_x, next_y, vars);
	if (tile == '1')
		return (0);
	else if (tile == 'C')
	{
		already_saved = 0;
		i = 0;
		while (i < vars->state.collectible_count)
		{
			if (vars->state.collectible_x[i] == next_x
				&& vars->state.collectible_y[i] == next_y)
			{
				already_saved = 1;
				break ;
			}
			i++;
		}
		if (!already_saved && vars->state.collectible_count < MAX_COLLECTIBLES)
		{
			vars->state.collectible_x[vars->state.collectible_count] = next_x;
			vars->state.collectible_y[vars->state.collectible_count] = next_y;
			vars->state.collectible_count++;
		}
	}
	else if (tile == 'E')
	{
		if (vars->map_info.all_collectible == vars->state.collectible_count)
			close_window(vars);
		else
			return (0);
	}
	vars->state.current_x = next_x;
	vars->state.current_y = next_y;
	vars->state.move_count++;
	printf("Move number: %d \n", vars->state.move_count);
	mlx_clear_window(vars->graphics.mlx, vars->graphics.win);
	read_and_display_map(vars);
	i = 0;
	while (i < vars->state.collectible_count)
	{
		mlx_put_image_to_window(vars->graphics.mlx, vars->graphics.win,
			vars->graphics.bg_img, vars->state.collectible_x[i],
			vars->state.collectible_y[i]);
		i++;
	}
	mlx_put_image_to_window(vars->graphics.mlx, vars->graphics.win,
		vars->graphics.bg_img, vars->state.start_pos_x,
		vars->state.start_pos_y);
	mlx_put_image_to_window(vars->graphics.mlx, vars->graphics.win,
		vars->graphics.player_img, vars->state.current_x,
		vars->state.current_y);
	return (0);
}
