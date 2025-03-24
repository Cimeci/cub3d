/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:33:41 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/24 15:55:28 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda(t_data *data)
{
    t_ray   *ray;

    ray = data->ray;
	int	i = 0;
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		// Calcul de la position et de la direction du rayon
		ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		// Coordonnée x dans l'espace caméra
		ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
		ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
		// Case de la map où nous nous trouvons
		ray->map_x = (int)ray->pos_x;
		ray->map_y = (int)ray->pos_y;
		// Longueur du rayon depuis la position actuelle jusqu'au prochain côté x ou y
		// Longueur du rayon d'un côté x ou y au prochain côté x ou y
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
		// Direction pour avancer dans la carte (soit +1, soit -1)
		ray->hit = 0; // Le mur a-t-il été touché ? 
		// Calcul de step et sideDist initial
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
		// Algorithme DDA (Digital Differential Analysis)
		while (ray->hit == 0)
		{
			// Saut à la prochaine case de la map, soit en x, soit en y
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
			// Vérifie si le rayon a touché un mur
			if (data->map[ray->map_x][ray->map_y] == '1')
				ray->hit = 1;
		}
		// Calcul de la distance projetée sur la direction de la caméra
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
		else
			ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
		// Calcul de la hauteur de la ligne à dessiner à l'écran
		ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
		// Calcul des pixels de début et fin les plus bas et hauts pour la bande actuelle
		ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray->draw_end >= SCREEN_HEIGHT)
			ray->draw_end = SCREEN_HEIGHT - 1;
		// Choisir une couleur en fonction du type de mur
		if (data->map[ray->map_x][ray->map_y] == '1')
			ray->img[i] = 0xFF0000; // Rouge
		else
			ray->img[i] = 0xFFFFFF; // Blanc
		// Donner une couleur différente selon l'orientation du mur
		if (ray->side == 1)
			ray->img[i] = ray->color / 2;
		i++;
	}
}