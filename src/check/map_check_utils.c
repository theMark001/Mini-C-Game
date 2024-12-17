/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 21:30:23 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/12/17 06:04:02 by marksylaiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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
	last_ber = ft_strnstr(path, extension, path_len);
	if (!last_ber)
		return (0);
	if (ft_strlen(last_ber) == ext_len)
		return (1);
	return (0);
}
