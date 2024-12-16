/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 03:36:46 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/12/16 04:15:35 by marksylaiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	open_map_file(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening map file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	set_img(t_vars *vars)
{
	int	img_width;
	int	img_height;

	vars->graphics.bg_img = mlx_xpm_file_to_image(vars->graphics.mlx,
			"textures/bg.xpm", &img_width, &img_height);
	vars->graphics.player_img = mlx_xpm_file_to_image(vars->graphics.mlx,
			"textures/player.xpm", &img_width, &img_height);
	vars->graphics.exit_img = mlx_xpm_file_to_image(vars->graphics.mlx,
			"textures/exit.xpm", &img_width, &img_height);
	vars->graphics.item_img = mlx_xpm_file_to_image(vars->graphics.mlx,
			"textures/item.xpm", &img_width, &img_height);
	vars->graphics.wall_img = mlx_xpm_file_to_image(vars->graphics.mlx,
			"textures/wall.xpm", &img_width, &img_height);
}

int	main(int ac, char **av)
{
	t_vars	vars;
	int		win_width;
	int		win_height;

	// Initialize the vars structure
	vars.state.collectible_count = 0;
	vars.state.move_count = 0;
	vars.state.initial_position_set = 0;

	if (ac != 2)
	{
		fprintf(stderr, "Usage: %s <map_file>\n", av[0]);
		return (EXIT_FAILURE);
	}

	vars.path = av[1];
	vars.graphics.mlx = mlx_init();
	if (!vars.graphics.mlx)
	{
		fprintf(stderr, "Error initializing MLX\n");
		return (EXIT_FAILURE);
	}

	get_map_info(&vars);
	if (map_check(&vars) == 1)
		exit(EXIT_FAILURE);

	vars.state.tile_size = 50;
	win_width = vars.map_info.width * vars.state.tile_size;
	win_height = vars.map_info.height * vars.state.tile_size;

	vars.graphics.win = mlx_new_window(vars.graphics.mlx, win_width, win_height,
			"Mini Game");
	if (!vars.graphics.win)
	{
		fprintf(stderr, "Error creating window\n");
		return (EXIT_FAILURE);
	}

	set_img(&vars);
	read_and_display_map(&vars);

	mlx_hook(vars.graphics.win, 2, 1L << 0, move_player, &vars);
	mlx_hook(vars.graphics.win, 17, 0, close_window, &vars);
	mlx_loop(vars.graphics.mlx);

	return (0);
}
