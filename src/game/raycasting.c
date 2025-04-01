/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:33:41 by inowak--          #+#    #+#             */
/*   Updated: 2025/04/01 11:10:33 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_data *data, t_ray *ray, int line_length, int x)
{
	int	texture;
	int color;
	int	pixel_index;
	double	step;
	double	tex_pos;
	int		tex_y;
	int	y;

	y = ray->draw_start;
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			texture = SO;
		else
			texture = NO;
	}
	else
	{
		if (ray->step_y > 0)
			texture = WE;
		else
			texture = EA;
	}
	step = 1.0 * 64 / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		int *texture_data = (int *)data->window->txr[texture].addr;
		color = texture_data[64 * tex_y + ray->tex_x];
		pixel_index = y * line_length + x;
		if (pixel_index >= 0 && pixel_index < SCREEN_HEIGHT * line_length)
			data->window->main->pixel_addr[pixel_index] = color;
		y++;
	}
}

void	handle_wall(t_ray *ray)
{
	// calcul de la distance au mur
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
	// calcul de la hauteur du mur a dessiner
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)64);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = 64 - ray->tex_x - 1;

}

void	ray_projection(t_data *data, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->map_x < 0 || ray->map_x >= data->map_height ||
            ray->map_y < 0 || ray->map_y >= data->map_width)
		{
            ray->hit = 1;
            break;
        }
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map[ray->map_x][ray->map_y] == '1')
			ray->hit = 1;
	}
}

void	handle_step(t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

void	dda(t_data *data)
{
	t_ray	*ray;
	int		line_length;
	int		x;

	ray = data->ray;
	data->window->main = data->window->main;
	data->window->main->pixel_addr = (int *)data->window->main->addr;
	line_length = data->window->main->size_line / 4;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
		ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
		ray->map_x = (int)ray->pos_x;
		ray->map_y = (int)ray->pos_y;
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
		ray->hit = 0;
		handle_step(ray);
		ray_projection(data, ray);
		handle_wall(ray);
		draw(data, ray, line_length, x);
		x++;
	}
}
