/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 21:30:23 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/12/17 06:24:07 by marksylaiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	count_map_chars(t_vars *vars)
{
	int		fd;
	char	buffer[1024];
	ssize_t	bytes_read;
	ssize_t	i;
	char	c;
	int		players;
	int		exits;
	int		collectibles;

	players = 0;
	exits = 0;
	collectibles = 0;
	fd = open_map_file(vars->path);
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			c = buffer[i++];
			if (c == 'C')
				collectibles++;
			else if (c == 'E')
				exits++;
			else if (c == 'P')
				players++;
		}
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	close(fd);
	vars->map_info.all_players = players;
	vars->map_info.all_exits = exits;
	vars->map_info.all_collectible = collectibles;
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
