/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:23:11 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/26 14:20:01 by inowak--         ###   ########.fr       */
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
}