/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:53:09 by inowak--          #+#    #+#             */
/*   Updated: 2025/04/01 17:27:51 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_horizontals(t_data *data, t_ray *ray, int dir)
{
	if (data->map[(int)(ray->pos_x + ray->dir_x * ray->move_speed * dir)]
		[(int)(ray->pos_y)] != '1')
		ray->pos_x += ray->dir_x * ray->move_speed * dir;
	if (data->map[(int)(ray->pos_x)]
		[(int)(ray->pos_y + ray->dir_y * ray->move_speed * dir)] != '1')
		ray->pos_y += ray->dir_y * ray->move_speed * dir;
}

static void	move_laterals(t_data *data, t_ray *ray, int dir)
{
	if (data->map[(int)(ray->pos_x - ray->dir_y * ray->move_speed * dir)]
		[(int)(ray->pos_y)] != '1')
		ray->pos_x -= ray->dir_y * ray->move_speed * dir;
	if (data->map[(int)(ray->pos_x)]
		[(int)(ray->pos_y + ray->dir_x * ray->move_speed * dir)] != '1')
		ray->pos_y += ray->dir_x * ray->move_speed * dir;
}

static void	rotate(t_ray *ray, int dir)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(ray->rot_speed * dir);
	sin_angle = sin(ray->rot_speed * dir);
	old_dir_x = ray->dir_x;
	ray->dir_x = ray->dir_x * cos_angle - ray->dir_y * sin_angle;
	ray->dir_y = old_dir_x * sin_angle + ray->dir_y * cos_angle ;
	old_plane_x = ray->plane_x;
	ray->plane_x = ray->plane_x * cos_angle - ray->plane_y * sin_angle;
	ray->plane_y = old_plane_x * sin_angle + ray->plane_y * cos_angle ;
}

void	moveplayer(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	if (data->window->keypress[SHIFT] == true)
		ray->move_speed = 0.02;
	if (data->window->keypress[W] == true)
		move_horizontals(data, ray, 1);
	if (data->window->keypress[S] == true)
		move_horizontals(data, ray, -1);
	if (data->window->keypress[A] == true)
		move_laterals(data, ray, 1);
	if (data->window->keypress[D] == true)
		move_laterals(data, ray, -1);
	if (data->window->keypress[RA] == true)
		rotate(ray, 1);
	if (data->window->keypress[LA] == true)
		rotate(ray, -1);
}
