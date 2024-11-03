/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:21:05 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/11/02 23:21:12 by marksylaiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_GAME_H
# define MINI_GAME_H

# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define MAX_COLLECTIBLES 100

typedef struct useless_1
{
	int				width;
	int				height;
	int				all_collectible;
	int				all_exits;
	int				all_players;
}					t_map_info;

typedef struct useless_2
{
	int				tile_size;
	int				current_x;
	int				current_y;
	int				start_pos_x;
	int				start_pos_y;
	int				initial_position_set;
	int				collectible_count;
	int				move_count;
	int				collectible_x[MAX_COLLECTIBLES];
	int				collectible_y[MAX_COLLECTIBLES];
}					t_game_state;

typedef struct useless_3
{
	void			*mlx;
	void			*win;
	void			*bg_img;
	void			*player_img;
	void			*exit_img;
	void			*item_img;
	void			*wall_img;
}					t_graphics;

typedef struct useless_4
{
	t_graphics		graphics;
	t_game_state	state;
	t_map_info		map_info;
	char			*path;
}					t_vars;

void				get_map_info(t_vars *vars);
int					map_check(t_vars *vars);
void				read_and_display_map(t_vars *vars);
int					move_player(int key, t_vars *vars);
int					close_window(t_vars *vars);

#endif