/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_enclosed_in_walls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:14:30 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/11/03 23:20:33 by marksylaiev      ###   ########.fr       */
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

int	check_line_length(int current_length, int *line_length)
{
	if (*line_length == -1)
		*line_length = current_length;
	return (*line_length == current_length);
}

int	process_line(char *line_start, int current_length, int is_first, int is_last)
{
	if ((is_first || is_last) && !process_wall_line(line_start, current_length))
		return (0);
	else if (!is_first && !process_side_walls(line_start, current_length))
		return (0);
	return (1);
}

int	read_and_process_buffer(char *buffer, ssize_t bytes_read, int *line_length)
{
	char	*line_start = buffer;
	int		current_length;
	int		is_first = 1;
	ssize_t	i = 0;

	while (i < bytes_read)
	{
		if (buffer[i] == '\n' || buffer[i] == '\0')
		{
			current_length = &buffer[i] - line_start;
			if (!check_line_length(current_length, line_length) ||
				!process_line(line_start, current_length, is_first, buffer[i + 1] == '\0'))
				return (0);
			line_start = &buffer[i + 1];
			is_first = 0;
		}
		i++;
	}
	return (1);
}

int	is_enclosed_in_walls(int fd)
{
	ssize_t	bytes_read;
	char	buffer[1024];
	int		line_length = -1;

	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		if (!read_and_process_buffer(buffer, bytes_read, &line_length))
			return (close(fd), 0);
	}
	close(fd);
	return (1);
}
