/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 07:29:37 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/20 08:21:16 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y <= end)
	{
		mlx_pixel_put(data->mlx, data->win, x, y, color);
		y++;
	}
}

void	raycasting(t_data *data)
{
	int x;
	for (x = 0; x < SCREEN_WIDTH; x++)
	{
		double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
		// Coordonnée X dans l'espace de la caméra
		double rayDirX = data->dirX + data->planeX * cameraX;
		double rayDirY = data->dirY + data->planeY * cameraX;

		// Position de départ du rayon
		int mapX = (int)data->posX;
		int mapY = (int)data->posY;

		// Longueur du rayon jusqu'au prochain côté X ou Y
		double sideDistX;
		double sideDistY;

		// Longueur du rayon d'un côté X ou Y au suivant
		double deltaDistX;
		double deltaDistY;

		if (rayDirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1 / rayDirX);
		if (rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1 / rayDirY);

		// Direction du rayon (pour savoir si on va à gauche/droite ou haut/bas)
		int stepX;
		int stepY;

		// Calculer stepX, stepY, sideDistX, sideDistY
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
		}

		// DDA (Digital Differential Analysis)
		int hit = 0; // A-t-on touché un mur ?
		int side;    // Quel côté du mur a été touché ?
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Vérifier si le rayon a touché un mur
			if (data->map[mapX][mapY] == '1')
				hit = 1;
		}

		// Calculer la distance jusqu'au mur
		double perpWallDist;
		if (side == 0)
			perpWallDist = (mapX - data->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - data->posY + (1 - stepY) / 2) / rayDirY;

		// Calculer la hauteur de la ligne à dessiner
		if (perpWallDist == 0)
			perpWallDist = 1;
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

		// Dessiner la colonne
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;

		// Choisir une couleur en fonction du côté du mur
		int color;
		if (side == 0)
			color = 0xFF0000; // Rouge pour les murs nord/sud
		else
			color = 0x00FF00; // Vert pour les murs est/ouest

		// Dessiner la colonne
		draw_vertical_line(data, x, drawStart, drawEnd, color);
	}
}