/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:49:13 by inowak--          #+#    #+#             */
/*   Updated: 2025/04/01 11:25:11 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	printf("Fenêtre fermée\n");
	if (data->window->main && data->window->main->img)
		mlx_destroy_image(data->window->mlx, data->window->main->img);
	if (data->window->win)
		mlx_destroy_window(data->window->mlx, data->window->win);
	if (data->window->mlx)
	{
		mlx_destroy_display(data->window->mlx);
		free(data->window->mlx);
	}
	free_all(data);
	exit(0);
}

int	key_press_move(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	if (keycode == KEY_W)
		data->window->keypress[W] = true;
	if (keycode == KEY_S)
		data->window->keypress[S] = true;
	if (keycode == KEY_A)
		data->window->keypress[A] = true;
	if (keycode == KEY_D)
		data->window->keypress[D] = true;
	if (keycode == KEY_LEFT)
		data->window->keypress[LA] = true;
	if (keycode == KEY_RIGHT)
		data->window->keypress[RA] = true;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->window->keypress[W] = false;
	if (keycode == KEY_S)
		data->window->keypress[S] = false;
	if (keycode == KEY_D)
		data->window->keypress[D] = false;
	if (keycode == KEY_A)
		data->window->keypress[A] = false;
	if (keycode == KEY_RIGHT)
		data->window->keypress[RA] = false;
	if (keycode == KEY_LEFT)
		data->window->keypress[LA] = false;
	return (0);
}