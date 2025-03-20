/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 07:28:15 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/20 07:28:36 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_data *data)
{
    // Position initiale du joueur (au milieu de la carte)
    data->posX = data->x + 0.5;
    data->posY = data->y + 0.5;

    // Direction initiale (regarde vers le nord)
    data->dirX = -1.0;
    data->dirY = 0.0;

    // Plan de la caméra (pour le FOV)
    data->planeX = 0.0;
    data->planeY = 0.66;

    // Vitesse de déplacement et de rotation
    data->moveSpeed = 0.1;
    data->rotSpeed = 0.1;
}