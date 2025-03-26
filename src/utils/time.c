/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:23:11 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/26 10:13:40 by inowak--         ###   ########.fr       */
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
	t_fps *fps;

    fps = data->fps;
	fps->old_time = fps->time;
	fps->time = get_time_in_ms() - fps->start_time;
	fps->frame_time = (fps->time - fps->old_time) / 1000.0;
	printf("fps: %f\n", 1.0 / fps->frame_time);
	data->ray->move_speed = fps->frame_time * SCREEN_WIDTH / 20;
	data->ray->rot_speed = fps->frame_time * SCREEN_WIDTH / 30;
}