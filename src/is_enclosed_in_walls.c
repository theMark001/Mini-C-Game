/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_enclosed_in_walls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:14:30 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/11/03 23:14:43 by marksylaiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	process_wall_line(const char *line, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	process_side_walls(const char *line, int length)
{
	return (line[0] == '1' && line[length - 1] == '1');
}

int	is_enclosed_in_walls(int fd)
{
	ssize_t	bytes_read;
	char	buffer[1024];
	char	*line_start;
	int		line_length;
	int		current_length;
	int		is_first;
	ssize_t	i;

	line_length = -1;
	is_first = 1;
	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		line_start = buffer;
		i = 0;
		while (i < bytes_read)
		{
			if (buffer[i] == '\n' || buffer[i] == '\0')
			{
				current_length = &buffer[i] - line_start;
				if (line_length == -1)
					line_length = current_length;
				if ((is_first || buffer[i + 1] == '\0')
					&& !process_wall_line(line_start, current_length))
					return (close(fd), 0);
				else if (!is_first && !process_side_walls(line_start,
						current_length))
					return (close(fd), 0);
				line_start = &buffer[i + 1];
				is_first = 0;
			}
			i++;
		}
	}
	return (close(fd), 1);
}
