/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 04:50:07 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/20 08:01:28 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_window(t_data *data)
{
    printf("Fenêtre fermée\n");
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    exit(0);
}

int key_press(int keycode, t_data *data)
{
    if (keycode == KEY_ESC)
		close_window(data);
    printf("Touche pressée: %d\n", keycode);
    return (0);
}

void display(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
        return;
    data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
    if (!data->win)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        return;
    }
    init_player(data);
    raycasting(data);
    mlx_hook(data->win, 2, 1L << 0, key_press, data);
    mlx_hook(data->win, 17, 1L << 17, close_window, data);
    mlx_loop(data->mlx);
}

