/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:33:41 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/21 14:57:26 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_ray(t_data *data)
{
    // Position initiale du joueur (au milieu de la carte)
    data->ray->pos_x = data->player->x + 0.5;
    data->ray->pos_y = data->player->y + 0.5;

    // Direction initiale (regarde vers le nord)
    data->ray->dir_x = -1.0;
    data->ray->dir_y = 0.0;

    // Plan de la caméra (pour le FOV)
    data->ray->plane_x = 0.0;
    data->ray->plane_y = 0.66;

    // Vitesse de déplacement et de rotation
    data->ray->move_speed = 0.1;
    data->ray->rot_speed = 0.1;
}

void    dda(t_data *data)
{
    double  camera_x;
    t_ray   *ray;

    ray = data->ray;
    camera_x = 2 * data->player->x / (double)WIN_WIDTH - 1;
    ray->ray_dir_x = ray->dir_x + ray->plane_x * camera_x;
    ray->ray_dir_y = ray->dir_y + ray->plane_y * camera_x;

    ray->delta_dist_x = abs(1 / ray->ray_dir_x);
    ray->delta_dist_y = abs(1 / ray->ray_dir_y);
    
    ray->map_x = (int)ray->pos_x;
    ray->map_y = (int)ray->pos_y;
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
    
    ray->hit = 0;
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
            ray->side_dist_x += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (data->map[ray->map_x][ray->map_y] > 0)
            ray->hit = 1;
    }

    if (ray->side == 0)
        ray->wall_dist = (ray->side_dist_x - ray->delta_dist_x);
    else
        ray->wall_dist = (ray->side_dist_y - ray->delta_dist_y);
    
    if (ray->side == WEST || ray->side == EAST)
        ray->wall_x = data->player->y + ray->wall_dist * ray->ray_dir_y;
    else
        ray->wall_x = data->player->x + ray->wall_dist * ray->ray_dir_x;
    ray->wall_x -= floor(ray->wall_x);
    data->line->x = ray->pos_x;

    if (data->map[ray->map_y][ray->map_x] == '1')
        paint_texture_line(data);
    data->line->y0 = 0;
    data->line->y1 = ray->draw_start;
    paint_line(data, data->window->c_color);
    data->line->y0 = WIN_HEIGHT;
    data->line->y1 = ray->draw_end;
    paint_line(data, data->window->f_color);
}

pixel_on_img(int rgb, int x, int y, t_image *img)
{
    int	r;
    int	g;
    int	b;

    r = (rgb >> 16) & 0xFF;
    g = (rgb >> 8) & 0xFF;
    b = rgb & 0xFF;
    img->data[y * img->line_length + x * img->bits_per_pixel / 8] = b;
    img->data[y * img->line_length + x * img->bits_per_pixel / 8 + 1] = g;
    img->data[y * img->line_length + x * img->bits_per_pixel / 8 + 2] = r;
}

void	paint_line(t_root *root, t_line *line, int rgb) // or paint_texture_line
{
	int	y;
	int	y_max;

	if (line->y0 < line->y1)
	{
		y = line->y0;
		y_max = line->y1;
	}
	else
	{
		y = line->y1;
		y_max = line->y0;
	}
	if (y >= 0)
	{
		while (y < y_max)
		{
			pixel_on_img(rgb, line->x, y, root->mlx_img);
			// or texture_on_img
			y++;
		}
	}
}
