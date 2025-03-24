/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:24:33 by ncharbog          #+#    #+#             */
/*   Updated: 2025/03/24 15:04:00 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_data *data)
{
	data->ray->dir_x = -1;
	data->ray->dir_y = 0;
	data->ray->plane_x = 0;
	data->ray->plane_y = 0.66;
}

void	init_data(t_data *data)
{
	data->window = malloc(sizeof(t_window));
	data->map = NULL;
	data->map_lst = NULL;
	data->player = malloc(sizeof(t_player));
	data->ray = malloc(sizeof(t_ray));
	ft_memset(data->ray, 0, sizeof(t_ray));
	init_ray(data);
}
