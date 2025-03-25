/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:33:41 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/25 19:20:59 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda(t_data *data)
{
	t_ray *ray = data->ray;
	t_img *img = data->window->main;    // Accès à la structure d'image
	int *pixel_addr = (int *)img->addr; // Adresse des pixels de l'image
	int line_length = img->size_line / 4;
	// Taille d'une ligne en pixels (divisé par 4 car int = 4 bytes)

	// printf("player: %f| %f\n", ray->pos_x, ray->pos_y);
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
		ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
		ray->map_x = (int)ray->pos_x;
		ray->map_y = (int)ray->pos_y;
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
		ray->hit = 0;

		if (ray->ray_dir_x < 0)
		{
			ray->step_x = -1;
			ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
		}
		else
		{
			ray->step_x = 1;
			ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x)
				* ray->delta_dist_x;
		}
		if (ray->ray_dir_y < 0)
		{
			ray->step_y = -1;
			ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
		}
		else
		{
			ray->step_y = 1;
			ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y)
				* ray->delta_dist_y;
		}

		while (ray->hit == 0)
		{
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

		if (ray->side == 0)
			ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x)
					/ 2) / ray->ray_dir_x;
		else
			ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y)
					/ 2) / ray->ray_dir_y;

		ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
		ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray->draw_end >= SCREEN_HEIGHT)
			ray->draw_end = SCREEN_HEIGHT - 1;

		int color;
		if (data->map[ray->map_x][ray->map_y] == '1')
			color = 0xFF0000;
		else
			color = 0xFFFFFF;

		if (ray->side == 1)
			color = color / 2;

		// Dessiner la bande verticale du mur
		for (int y = ray->draw_start; y < ray->draw_end; y++)
		{
			int pixel_index = y * line_length + x;
			if (pixel_index >= 0 && pixel_index < SCREEN_HEIGHT * line_length)
				pixel_addr[pixel_index] = color;
		}
	}
}