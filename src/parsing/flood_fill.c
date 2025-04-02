/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 02:00:02 by inowak--          #+#    #+#             */
/*   Updated: 2025/04/02 11:07:44 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_position(char **map, int y, int x)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x])
		return (false);
	return (true);
}

bool	flood_fill(char **map, int y, int x)
{
	if (!is_valid_position(map, y, x))
		return (false);
	if (map[y][x] == '1')
		return (true);
	if (map[y][x] == 'X')
		return (true);
	map[y][x] = 'X';
	if (!flood_fill(map, y + 1, x) || !flood_fill(map, y - 1, x)
		|| !flood_fill(map, y, x + 1) || !flood_fill(map, y, x - 1))
		return (false);
	return (true);
}
