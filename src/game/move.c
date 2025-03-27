/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:53:09 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/27 18:49:43 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_horizontals(t_data *data, t_ray *ray, int utils)
{
	double	tmp_posx;
	double	tmp_posy;

	if (utils == 1)
	{
		tmp_posx = ray->pos_x + (ray->dir_x * ray->move_speed);
		tmp_posy = ray->pos_y + (ray->dir_y * ray->move_speed);
		if (data->map[(int)tmp_posx][(int)tmp_posy] != '1')
		{
			ray->pos_x += ray->dir_x * ray->move_speed;
			ray->pos_y += ray->dir_y * ray->move_speed;
		}
		return ;
	}
	tmp_posx = ray->pos_x - (ray->dir_x * ray->move_speed);
	tmp_posy = ray->pos_y - (ray->dir_y * ray->move_speed);
	if (data->map[(int)tmp_posx][(int)tmp_posy] != '1')
	{
		ray->pos_x -= ray->dir_x * ray->move_speed;
		ray->pos_y -= ray->dir_y * ray->move_speed;
	}
}

static void	move_laterals(t_data *data, t_ray *ray, int utils)
{
	double	perp_dir_x;
	double	perp_dir_y;
	double	tmp_posx;
	double	tmp_posy;

	if (utils == 1)
	{
		perp_dir_x = -ray->dir_y;
		perp_dir_y = ray->dir_x;
		tmp_posx = ray->pos_x + (perp_dir_x * ray->move_speed);
		tmp_posy = ray->pos_y + (perp_dir_y * ray->move_speed);
		if (data->map[(int)tmp_posx][(int)ray->pos_y] != '1')
			ray->pos_x += perp_dir_x * ray->move_speed;
		if (data->map[(int)ray->pos_x][(int)tmp_posy] != '1')
			ray->pos_y += perp_dir_y * ray->move_speed;
		return ;
	}
	perp_dir_x = ray->dir_y;
	perp_dir_y = -ray->dir_x;
	tmp_posx = ray->pos_x + (perp_dir_x * ray->move_speed);
	tmp_posy = ray->pos_y + (perp_dir_y * ray->move_speed);
	if (data->map[(int)tmp_posx][(int)ray->pos_y] != '1')
		ray->pos_x += perp_dir_x * ray->move_speed;
	if (data->map[(int)ray->pos_x][(int)tmp_posy] != '1')
		ray->pos_y += perp_dir_y * ray->move_speed;
}

static void	rotate(t_data *data, t_ray *ray, int utils)
{
	double	old_dirx;
	double	old_planex;

	old_planex = ray->plane_x;
	old_dirx = data->ray->dir_x;
	if (utils == 1)
	{
		ray->dir_x = ray->dir_x * cos(-ray->rot_speed) - ray->dir_y
			* sin(-ray->rot_speed);
		ray->dir_y = old_dirx * sin(-ray->rot_speed) + ray->dir_y
			* cos(-ray->rot_speed);
		ray->plane_x = ray->plane_x * cos(-ray->rot_speed) - ray->plane_y
			* sin(-ray->rot_speed);
		ray->plane_y = old_planex * sin(-ray->rot_speed) + ray->plane_y
			* cos(-ray->rot_speed);
		return ;
	}
	ray->dir_x = ray->dir_x * cos(ray->rot_speed) - ray->dir_y
		* sin(ray->rot_speed);
	ray->dir_y = old_dirx * sin(ray->rot_speed) + ray->dir_y
		* cos(ray->rot_speed);
	ray->plane_x = ray->plane_x * cos(ray->rot_speed) - ray->plane_y
		* sin(ray->rot_speed);
	ray->plane_y = old_planex * sin(ray->rot_speed) + ray->plane_y
		* cos(ray->rot_speed);
}

void	moveplayer(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	if (data->window->keypress[W] == true)
		move_horizontals(data, ray, 1);
	if (data->window->keypress[S] == true)
		move_horizontals(data, ray, 0);
	if (data->window->keypress[A] == true)
		move_laterals(data, ray, 1);
	if (data->window->keypress[D] == true)
		move_laterals(data, ray, 0);
	if (data->window->keypress[LA] == true)
		rotate(data, ray, 1);
	if (data->window->keypress[RA] == true)
		rotate(data, ray, 0);
}
