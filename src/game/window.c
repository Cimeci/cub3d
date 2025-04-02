/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 04:50:07 by inowak--          #+#    #+#             */
/*   Updated: 2025/04/02 09:30:30 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_bg(t_data *data)
{
	t_img	*img;
	int		*pixel_addr;
	int		pixel_index;
	int		x;
	int		y;

	x = -1;
	img = data->window->main;
	pixel_addr = (int *)img->addr;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT)
		{
			pixel_index = y * img->size_line / 4 + x;
			if (pixel_index >= 0 && pixel_index < (SCREEN_HEIGHT * \
				img->size_line / 8))
				pixel_addr[pixel_index] = data->window->c_color;
			else
				pixel_addr[pixel_index] = data->window->f_color;
		}
	}
}

static bool	is_moved(t_window *win)
{
	int	i;

	i = 1;
	if (win->keypress[0] == true)
	{
		win->keypress[0] = false;
		return (true);
	}
	while (i < 8)
	{
		if (win->keypress[i] == true)
			return (true);
		i++;
	}
	return (false);
}

static int	ft_raycasting(t_data *data)
{
	char	*fps;

	if (is_moved(data->window))
	{
		set_fps(data);
		moveplayer(data);
		fps = ft_itoa((int)ceil(1.0 / data->fps->frame_time));
		draw_bg(data);
		dda(data);
		mlx_put_image_to_window(data->window->mlx, data->window->win,
			data->window->main->img, 0, 0);
		mlx_string_put(data->window->mlx, data->window->win, 10, 15, 0xffffff,
			"fps: ");
		mlx_string_put(data->window->mlx, data->window->win, 40, 16, 0xffffff,
			fps);
		free(fps);
	}
	return (0);
}

void	display(t_data *data)
{
	data->window->mlx = mlx_init();
	if (!data->window->mlx || !data->window->main)
		print_error_exit("Failed to initialize the mlx", data);
	init_texture(data);
	data->window->win = mlx_new_window(data->window->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D");
	if (!data->window->win)
		print_error_exit("Failed to initialize the window", data);
	data->window->main->img = mlx_new_image(data->window->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	if (!data->window->main->img)
		print_error_exit("Failed to create an image", data);
	data->window->main->addr = mlx_get_data_addr(data->window->main->img,
			&data->window->main->bpp, &data->window->main->size_line,
			&data->window->main->endian);
	mlx_hook(data->window->win, 17, 1L << 17, close_window, data);
	mlx_hook(data->window->win, KeyPress, KeyPressMask, key_press_move, data);
	mlx_hook(data->window->win, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_loop_hook(data->window->mlx, ft_raycasting, data);
	mlx_loop(data->window->mlx);
}
