/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 04:50:07 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/25 10:04:42 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	printf("Fenêtre fermée\n");
	mlx_destroy_window(data->window->mlx, data->window->win);
	mlx_destroy_display(data->window->mlx);
	free(data->window->mlx);
	exit(0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	printf("Touche pressée: %d\n", keycode);
	return (0);
}


void	display(t_data *data)
{	
	data->window->mlx = mlx_init();
	if (!data->window->mlx)
        return ;  
	data->window->win = mlx_new_window(data->window->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D");
	if (!data->window->win)
	{
		mlx_destroy_display(data->window->mlx);
		free(data->window->mlx);
		return ;
	} 
	void	*img_ptr = mlx_new_image(data->window->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_get_data_addr(img_ptr, &data->window->main->bpp, &data->window->main->size_line, &data->window->main->endian);
	dda(data);
	mlx_put_image_to_window(data->window->mlx, data->window->win, data->ray->img, 0, 0);
	mlx_hook(data->window->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->window->win, 17, 1L << 17, close_window, data);
	mlx_loop(data->window->mlx);
}
