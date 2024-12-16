/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msylaiev <msylaiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:21:05 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/11/23 20:30:42 by msylaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER
# define HEADER

# include "mlx.h" 		// For mlx funcs
# include <fcntl.h>  // For open() and O_RDONLY
# include <stdio.h>  // For perror()
# include <stdlib.h> // For exit() and EXIT_FAILURE
# include <unistd.h> // For close(), read(), ssize_t

#define KEY_W 119     
#define KEY_A 97    
#define KEY_S 115    
#define KEY_D 100    
#define KEY_ESC 65307 

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

typedef struct t_graphics
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
char				next_px(int next_x, int next_y, t_vars *vars);

int					close_window(t_vars *vars);
int					open_map_file(const char *path);
int					is_enclosed_in_walls(int fd);
int					ft_printf(const char *format, ...);

#endif