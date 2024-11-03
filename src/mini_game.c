/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:21:05 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/11/03 03:13:59 by marksylaiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_game.h"

int	main(void)
{
	t_vars		vars;
	int			win_width;
	int			win_height;

	// Setting up MLX
	vars.graphics.mlx = mlx_init();
	vars.state.initial_position_set = 0;
	// Setting up Window
	get_map_info("maps/map.ber", &vars);
	if (map_check(&vars) == 1) {
		exit (0);
	}
	vars.state.tile_size = 50;
	win_width = vars.map_info.width * vars.state.tile_size;
	win_height = vars.map_info.height * vars.state.tile_size;
	vars.graphics.win = mlx_new_window(vars.graphics.mlx, win_width, win_height,
			"Mini Game");
	// Setting up Imgs
	int img_width, img_height;
	vars.graphics.bg_img = mlx_xpm_file_to_image(vars.graphics.mlx,
			"textures/bg.xpm", &img_width, &img_height);
	vars.graphics.player_img = mlx_xpm_file_to_image(vars.graphics.mlx,
			"textures/player.xpm", &img_width, &img_height);
	vars.graphics.exit_img = mlx_xpm_file_to_image(vars.graphics.mlx,
			"textures/exit.xpm", &img_width, &img_height);
	vars.graphics.item_img = mlx_xpm_file_to_image(vars.graphics.mlx,
			"textures/item.xpm", &img_width, &img_height);
	vars.graphics.wall_img = mlx_xpm_file_to_image(vars.graphics.mlx,
			"textures/wall.xpm", &img_width, &img_height);
	// Display Imgs
	read_and_display_map(&vars, "maps/map.ber");
	// Setting up Movements
	mlx_hook(vars.graphics.win, 2, 1L << 0, move_player, &vars);
	// Set the close event hook to listen for the X button
	mlx_hook(vars.graphics.win, 17, 0, close_window, &vars);
	mlx_loop(vars.graphics.mlx);
	return (0);
}
