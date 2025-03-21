/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:24:33 by ncharbog          #+#    #+#             */
/*   Updated: 2025/03/21 14:53:56 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->window = malloc(sizeof(t_window));
	data->map = NULL;
	data->map_lst = NULL;
	data->player = malloc(sizeof(t_player));
	data->ray = malloc(sizeof(t_ray));
	data->line = malloc(sizeof(t_line));
	data->image = malloc(sizeof(t_image));
	init_ray(data);
}
