/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 02:00:02 by inowak--          #+#    #+#             */
/*   Updated: 2025/04/17 16:04:07 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_position(char **map, int y, int x, int i)
{
	if (y < 0 || x < 0 || !map[x] || !map[x][y] || i > 1500)
		return (false);
	return (true);
}

bool	flood_fill(char **map, int y, int x, int i)
{
	if (!is_valid_position(map, y, x, i))
		return (false);
	if (map[x][y] == '1')
		return (true);
	if (map[x][y] == 'X')
		return (true);
	map[x][y] = 'X';
	if (!flood_fill(map, y + 1, x, i + 1) || !flood_fill(map, y - 1, x, i + 1)
		|| !flood_fill(map, y, x + 1, i + 1)
		|| !flood_fill(map, y, x - 1, i + 1))
		return (false);
	return (true);
}
