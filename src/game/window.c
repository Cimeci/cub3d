/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 04:50:07 by inowak--          #+#    #+#             */
/*   Updated: 2025/04/01 09:53:42 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_bg(t_data *data)
{
	t_img	*img;
	int		*pixel_addr;
	int		line_length;
	int		pixel_index;

	img = data->window->main;
	pixel_addr = (int *)img->addr;
	line_length = img->size_line / 4;
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			pixel_index = y * line_length + x;
			if (pixel_index >= 0 && pixel_index < (SCREEN_HEIGHT * line_length
					/ 2))
				pixel_addr[pixel_index] = data->window->c_color;
			else
				pixel_addr[pixel_index] = data->window->f_color;
		}
	}
}

bool	is_moved(t_window *win)
{
	int	i;
	if (win->keypress[0] == true)
	{
		win->keypress[0] = false;
		return (true);
	}
	i = 1;
	while (i < 7)
	{
		if (win->keypress[i] == true)
			return (true);
		i++;
	}
	return (false);
}

int	ft_raycasting(t_data *data)
{
	if (is_moved(data->window))
	{
		moveplayer(data);
		set_fps(data);
		draw_bg(data);
		dda(data);
		mlx_put_image_to_window(data->window->mlx, data->window->win,
			data->window->main->img, 0, 0);
		mlx_string_put(data->window->mlx, data->window->win, 10, 15, 0xffffff,
			"fps: ");
		mlx_string_put(data->window->mlx, data->window->win, 40, 16, 0xffffff,
			ft_itoa((int)ceil(1.0 / data->fps->frame_time)));
	}
	return (0);
}

void	display(t_data *data)
{
	data->window->mlx = mlx_init();
	if (!data->window->mlx || !data->window->main)
		return ;
	init_texture(data);
	data->window->win = mlx_new_window(data->window->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D");
	if (!data->window->win)
	{
		mlx_destroy_display(data->window->mlx);
		free(data->window->mlx);
		return ;
	}
	data->window->main->img = mlx_new_image(data->window->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	if (!data->window->main->img)
	{
		mlx_destroy_window(data->window->mlx, data->window->win);
		mlx_destroy_display(data->window->mlx);
		free(data->window->mlx);
		return ;
	}
	data->window->main->addr = mlx_get_data_addr(data->window->main->img,
			&data->window->main->bpp, &data->window->main->size_line,
			&data->window->main->endian);
	mlx_hook(data->window->win, 17, 1L << 17, close_window, data);
	mlx_hook(data->window->win, KeyPress, KeyPressMask, key_press_move, data);
	mlx_hook(data->window->win, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_loop_hook(data->window->mlx, ft_raycasting, data);
	mlx_loop(data->window->mlx);
}
