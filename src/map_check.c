/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 21:30:23 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/11/03 22:29:40 by marksylaiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	is_rectangular(const char *path)
{
	int		fd;
	ssize_t	bytes_read;
	char	buffer[1024];
	int		first_length;
	int		current_length;
	ssize_t	i;

	first_length = -1;
	current_length = 0;
	i = 0;
	fd = open_map_file(path);
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			if (!read_and_check_line(&current_length, &first_length, buffer[i]))
				return (close(fd), 0);
			i++;
		}
	}
	close(fd);
	return (first_length == -1 || current_length == first_length);
}

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

int	is_enclosed_in_walls(const char *path)
{
	int		fd;
	ssize_t	bytes_read;
	char	buffer[1024];
	char	*line_start;
	int		line_length;
	int		current_length;
	int		is_first;
	ssize_t	i;

	line_length = -1;
	is_first = 1;
	fd = open_map_file(path);
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

int	map_check_conditions(t_vars *vars)
{
	if (vars->map_info.all_players != 1)
	{
		printf("Error: map should contain exactly one player.\n");
		return (1);
	}
	if (vars->map_info.all_exits != 1)
	{
		printf("Error: map should contain exactly one exit.\n");
		return (1);
	}
	if (vars->map_info.all_collectible < 1)
	{
		printf("Error: map should contain at least one collectible.\n");
		return (1);
	}
	return (0);
}

int	map_check(t_vars *vars)
{
	if (map_check_conditions(vars))
		return (1);
	if (!is_rectangular(vars->path))
	{
		printf("Error: map is not rectangular.\n");
		return (1);
	}
	if (!is_enclosed_in_walls(vars->path))
	{
		printf("Error: map is not enclosed in walls.\n");
		return (1);
	}
	return (0);
}