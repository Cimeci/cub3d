/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:24:33 by ncharbog          #+#    #+#             */
/*   Updated: 2025/03/25 19:03:58 by inowak--         ###   ########.fr       */
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

void	init_fps(t_fps *fps)
{
	fps->start_time = get_time_in_ms();
	fps->old_time = 0;
	fps->time = 0;
	fps->frame_time = 0;
}

void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	
	data->window = malloc(sizeof(t_window));
	if (!data->window)
		return ;
	data->map = NULL;
	data->map_lst = NULL;
	data->player = malloc(sizeof(t_player));
	if (!data->player)
	{
		free(data->window);
		return ;
	}
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
	{
		free(data->window);
		free(data->player);
		return ;
	}
	ft_memset(data->ray, 0, sizeof(t_ray));
	data->window->main = malloc(sizeof(t_img));
	if (!data->window->main)
	{
		free(data->window);
		free(data->player);
		free(data->ray);
		return ;
	}
	ft_memset(data->window->main, 0, sizeof(t_img));
	data->fps = malloc(sizeof(t_fps));
	if (!data->fps)
	{
		free(data->window->main);
		free(data->window);
		free(data->player);
		free(data->ray);
		return ;
	}
	init_ray(data);
	init_fps(data->fps);
	ft_memset(data->window->keypress, 0, 7);
	data->window->keypress[0] = true;
}
