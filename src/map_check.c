/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marksylaiev <marksylaiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:21:05 by marksylaiev       #+#    #+#             */
/*   Updated: 2024/11/03 03:08:14 by marksylaiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_game.h"

int map_check(t_vars *vars) {
	if(vars->map_info.all_players != 1) {
		printf("Error not one player\n");
		return 1;
	}
	else if(vars->map_info.all_exits != 1) {
		printf("Error not one exit\n");
		return 1;
	}
	else if(vars->map_info.all_collectible < 1) {
		printf("Error less then one collectible \n");
		return 1;
	}
	return 0;
}