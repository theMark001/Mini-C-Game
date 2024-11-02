/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:21:05 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/11/02 23:38:22 by marksylaiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_game.h"

t_map_info	get_map_info(const char *filename)
{
	int			fd;
	t_map_info	size = {0, 0, 0};
	ssize_t		bytes_read;
	char		buffer[1024];
	int			is_first_line;

	fd = open(filename, O_RDONLY);
	is_first_line = 1;
	
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
	{
		for (ssize_t i = 0; i < bytes_read; i++)
		{
			if (buffer[i] == '\n')
			{
				size.height++;
				is_first_line = 0;
			}
			else
			{
				if (is_first_line)
					size.width++;
				if (buffer[i] == 'C')
					size.all_collectible++;
			}
		}
	}
	size.height += 1;
	close(fd);
	return (size);
}
