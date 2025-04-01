/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:23:11 by inowak--          #+#    #+#             */
/*   Updated: 2025/04/01 15:53:04 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

void	set_fps(t_data *data)
{
	t_fps	*fps;

	fps = data->fps;
	fps->old_time = fps->time;
	fps->time = get_time_in_ms() - fps->start_time;
	fps->frame_time = fps->time - fps->old_time;
	data->ray->move_speed = 0.008;
	data->ray->rot_speed = 0.006;
}
