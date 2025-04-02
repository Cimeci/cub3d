/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:24:33 by ncharbog          #+#    #+#             */
/*   Updated: 2025/04/02 15:36:42 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycasting(t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
	ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

static void	init_ray(t_data *data)
{
	data->ray->dir_x = 0;
	data->ray->dir_y = 0;
	data->ray->plane_x = 0.66;
	data->ray->plane_y = 0;
	if (data->ray->ort == 'E')
		data->ray->dir_y = 1;
	else if (data->ray->ort == 'W')
	{
		data->ray->dir_y = -1;
		data->ray->plane_x = -0.66;
	}
	else if (data->ray->ort == 'S')
	{
		data->ray->dir_x = 1;
		data->ray->plane_x = 0;
		data->ray->plane_y = 0.66;
	}
	else if (data->ray->ort == 'N')
	{
		data->ray->dir_x = -1;
		data->ray->plane_x = 0;
		data->ray->plane_y = -0.66;
	}
}

static void	init_fps(t_fps *fps)
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
	data->window = malloc(sizeof(t_window));
	if (!data->window)
		print_error_exit("Malloc error", data);
	ft_memset(data->window, 0, sizeof(t_window));
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		print_error_exit("Malloc error", data);
	ft_memset(data->ray, 0, sizeof(t_ray));
}
