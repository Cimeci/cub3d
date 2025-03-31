/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:23:11 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/31 15:49:10 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	set_fps(t_data *data)
{
	t_fps	*fps;
	double	tmp;

	fps = data->fps;
	fps->old_time = fps->time;
	fps->time = get_time_in_ms() - fps->start_time;
	fps->frame_time = (fps->time - fps->old_time) / 1000.0;
	tmp = fps->frame_time;
	// data->ray->move_speed = tmp * 3.0;
	// data->ray->rot_speed = tmp * 1.5;
	data->ray->move_speed = 0.01;
	data->ray->rot_speed = 0.005 ;
}
