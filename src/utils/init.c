/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:24:33 by ncharbog          #+#    #+#             */
/*   Updated: 2025/04/01 17:13:22 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_data *data)
{
	if (data->player->or == 'E')
	{
		data->ray->dir_x = 0;
		data->ray->dir_y = -1;
		data->ray->plane_x = 0.66;
		data->ray->plane_y = 0;
	}
	else if (data->player->or == 'W')
	{
		data->ray->dir_x = 0;
		data->ray->dir_y = 1;
		data->ray->plane_x = -0.66;
		data->ray->plane_y = 0;
	}
	else if (data->player->or == 'S')
	{
		data->ray->dir_x = 1;
		data->ray->dir_y = 0;
		data->ray->plane_x = 0;
		data->ray->plane_y = 0.66;
	}
	else if (data->player->or == 'N')
	{
		data->ray->dir_x = -1;
		data->ray->dir_y = 0;
		data->ray->plane_x = 0;
		data->ray->plane_y = -0.66;
	}
}

void	init_fps(t_fps *fps)
{
	fps->start_time = get_time_in_ms();
	fps->old_time = 0;
	fps->time = 0;
	fps->frame_time = 0;
}

void	init_game(t_data *data)
{
	data->window->txr = malloc(sizeof(t_img) * 5);
	ft_memset(data->window->txr, 0, sizeof(t_img) * 4);
	data->window->main = malloc(sizeof(t_img));
	ft_memset(data->window->main, 0, sizeof(t_img));
	data->fps = malloc(sizeof(t_fps));
	init_ray(data);
	init_fps(data->fps);
	ft_memset(data->window->keypress, 0, 8);
	data->window->keypress[0] = true;
}

void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->map = NULL;
	data->map_lst = NULL;
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		print_error_exit("Malloc error", data);
	data->window = malloc(sizeof(t_window));
	if (!data->window)
		print_error_exit("Malloc error", data);
	ft_memset(data->window, 0, sizeof(t_window));
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		print_error_exit("Malloc error", data);
	ft_memset(data->ray, 0, sizeof(t_ray));
}
