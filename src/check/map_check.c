/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 21:30:23 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/12/17 05:54:54 by marksylaiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_and_update_length(int *current_length, int *first_length)
{
	if (*first_length == -1)
		*first_length = *current_length;
	else if (*current_length != *first_length)
		return (0);
	*current_length = 0;
	return (1);
}

int	read_and_check_line(int *current_length, int *first_length, char c)
{
	if (c == '\n')
		return (check_and_update_length(current_length, first_length));
	(*current_length)++;
	return (1);
}

int	is_rectangular(int fd)
{
	ssize_t	bytes_read;
	char	buffer[1024];
	int		first_length;
	int		current_length;
	ssize_t	i;

	first_length = -1;
	current_length = 0;
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			if (!read_and_check_line(&current_length, &first_length, buffer[i]))
				return (close(fd), 0);
			i++;
		}
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	close(fd);
	return (first_length == -1 || current_length == first_length);
}

int	map_check_conditions(t_vars *vars)
{
	if (vars->map_info.all_players != 1)
	{
		ft_printf("Error: map should contain exactly one player.\n");
		return (1);
	}
	if (vars->map_info.all_exits != 1)
	{
		ft_printf("Error: map should contain exactly one exit.\n");
		return (1);
	}
	if (vars->map_info.all_collectible < 1)
	{
		ft_printf("Error: map should contain at least one collectible.\n");
		return (1);
	}
	return (0);
}

/*
** New function: count_map_chars
** Reads the entire map file once, counting the number of 'P', 'E', 'C',
** as well as determining width and height.
*/

int	count_map_chars(t_vars *vars)
{
	int		fd;
	char	buffer[1024];
	ssize_t	bytes_read;
	ssize_t	i;
	int		is_first_line;
	char	c;

	int players, exits, collectibles;
	int width, height;
	players = 0;
	exits = 0;
	collectibles = 0;
	width = 0;
	height = 0;
	is_first_line = 1;
	fd = open_map_file(vars->path);
	if (fd < 0)
	{
		ft_printf("Error: Unable to open map file for counting.\n");
		return (0);
	}
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			c = buffer[i++];
			if (c == '\n')
			{
				height++;
				if (is_first_line)
					is_first_line = 0;
			}
			else
			{
				if (is_first_line)
					width++;
				if (c == 'C')
					collectibles++;
				else if (c == 'E')
					exits++;
				else if (c == 'P')
					players++;
			}
		}
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	close(fd);
	// If the file doesn't end with a newline, we might need to count
	// the last line if it contains characters.
	if (width > 0 && is_first_line == 1)
		height = 1;
	else if (width > 0 && !is_first_line)
		height++;
	vars->map_info.width = width;
	vars->map_info.height = height;
	vars->map_info.all_players = players;
	vars->map_info.all_exits = exits;
	vars->map_info.all_collectible = collectibles;
	return (1);
}

#include "libft.h" // For ft_strlen and ft_strrchr

int	has_valid_extension(const char *path)
{
	const char	*extension = ".ber";
	size_t		path_len;
	size_t		ext_len;
	char		*last_ber;

	path_len = ft_strlen(path);
	ext_len = ft_strlen(extension);
	if (path_len < ext_len)
		return (0);
	// Find the last occurrence of ".ber"
	last_ber = ft_strnstr(path, extension, path_len);
	// If no ".ber" is found, return 0
	if (!last_ber)
		return (0);
	// Check if the last occurrence of ".ber" is exactly at the end of the string
	if (ft_strlen(last_ber) == ext_len)
		return (1);
	return (0);
}

int	map_check(t_vars *vars)
{
	// First, count the characters in the map
	if (!count_map_chars(vars))
		return (1);

	// Now we can safely check conditions as vars->map_info is populated
	if (map_check_conditions(vars))
		return (1);

	// Check if map is rectangular
	{
		int fd = open_map_file(vars->path);
		if (!is_rectangular(fd))
		{
			ft_printf("Error: map is not rectangular.\n");
			return (1);
		}
	}

	// Check if map is enclosed in walls
	{
		int fd = open_map_file(vars->path);
		if (!is_enclosed_in_walls(fd))
		{
			ft_printf("Error: map is not enclosed in walls.\n");
			return (1);
		}
	}

	return (0);
}