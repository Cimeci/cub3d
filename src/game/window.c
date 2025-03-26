/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 04:50:07 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/26 11:32:23 by inowak--         ###   ########.fr       */
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
	exit(0);
}

int	key_press_move(int keycode, t_data *data)
{
	t_ray	*ray;
	double	old_dirx;
	double	old_planex;
	double	tmp_posx;
	double	tmp_posy;
	double	perp_dir_x;
	double	perp_dir_y;

	ray = data->ray;
	tmp_posx = ray->pos_x;
	tmp_posy = ray->pos_y;
	old_planex = ray->plane_x;
	old_dirx = data->ray->dir_x;
	if (keycode == KEY_ESC)
		close_window(data);
	else if (keycode == KEY_W)
	{
		tmp_posx = ray->pos_x + (ray->dir_x * ray->move_speed);
		tmp_posy = ray->pos_y + (ray->dir_y * ray->move_speed);
		if (data->map[(int)tmp_posx][(int)tmp_posy] != '1')
		{
			ray->pos_x += ray->dir_x * ray->move_speed;
			ray->pos_y += ray->dir_y * ray->move_speed;
		}
		data->window->keypress[W] = true;
	}
	else if (keycode == KEY_S)
	{
		tmp_posx = ray->pos_x - (ray->dir_x * ray->move_speed);
		tmp_posy = ray->pos_y - (ray->dir_y * ray->move_speed);
		if (data->map[(int)tmp_posx][(int)tmp_posy] != '1')
		{
			ray->pos_x -= ray->dir_x * ray->move_speed;
			ray->pos_y -= ray->dir_y * ray->move_speed;
		}
		data->window->keypress[S] = true;
	}
	else if (keycode == KEY_D)
	{
		perp_dir_x = -ray->dir_y;
		perp_dir_y = ray->dir_x;
		tmp_posx = ray->pos_x + (perp_dir_x * ray->move_speed);
		tmp_posy = ray->pos_y + (perp_dir_y * ray->move_speed);
		if (data->map[(int)tmp_posx][(int)ray->pos_y] != '1')
			ray->pos_x += perp_dir_x * ray->move_speed;
		if (data->map[(int)ray->pos_x][(int)tmp_posy] != '1')
			ray->pos_y += perp_dir_y * ray->move_speed;
		data->window->keypress[D] = true;
	}
	else if (keycode == KEY_A)
	{
		perp_dir_x = ray->dir_y;
		perp_dir_y = -ray->dir_x;
		tmp_posx = ray->pos_x + (perp_dir_x * ray->move_speed);
		tmp_posy = ray->pos_y + (perp_dir_y * ray->move_speed);
		if (data->map[(int)tmp_posx][(int)ray->pos_y] != '1')
			ray->pos_x += perp_dir_x * ray->move_speed;
		if (data->map[(int)ray->pos_x][(int)tmp_posy] != '1')
			ray->pos_y += perp_dir_y * ray->move_speed;
		data->window->keypress[A] = true;
	}
	else if (keycode == KEY_RIGHT)
	{
		ray->dir_x = ray->dir_x * cos(-ray->rot_speed) - ray->dir_y
			* sin(-ray->rot_speed);
		ray->dir_y = old_dirx * sin(-ray->rot_speed) + ray->dir_y
			* cos(-ray->rot_speed);
		ray->plane_x = ray->plane_x * cos(-ray->rot_speed) - ray->plane_y
			* sin(-ray->rot_speed);
		ray->plane_y = old_planex * sin(-ray->rot_speed) + ray->plane_y
			* cos(-ray->rot_speed);
		data->window->keypress[RA] = true;
	}
	else if (keycode == KEY_LEFT)
	{
		ray->dir_x = ray->dir_x * cos(ray->rot_speed) - ray->dir_y
			* sin(ray->rot_speed);
		ray->dir_y = old_dirx * sin(ray->rot_speed) + ray->dir_y
			* cos(ray->rot_speed);
		ray->plane_x = ray->plane_x * cos(ray->rot_speed) - ray->plane_y
			* sin(ray->rot_speed);
		ray->plane_y = old_planex * sin(ray->rot_speed) + ray->plane_y
			* cos(ray->rot_speed);
		data->window->keypress[LA] = true;
	}
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->window->keypress[W] = false;
	else if (keycode == KEY_S)
		data->window->keypress[S] = false;
	else if (keycode == KEY_D)
		data->window->keypress[D] = false;
	else if (keycode == KEY_A)
		data->window->keypress[A] = false;
	else if (keycode == KEY_RIGHT)
		data->window->keypress[RA] = false;
	else if (keycode == KEY_LEFT)
		data->window->keypress[LA] = false;
	return (0);
}

void	clear_window(t_data *data)
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
			if (pixel_index >= 0 && pixel_index < (SCREEN_HEIGHT * line_length / 2))
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
		{
			// printf("keypress: %d\n", i);
			return (true);
		}
		i++;
	}
	return (false);
}

int	ft_raycasting(t_data *data)
{
	if (is_moved(data->window))
	{
		set_fps(data);
		clear_window(data);
		dda(data);
		mlx_put_image_to_window(data->window->mlx, data->window->win,
			data->window->main->img, 0, 0);
	}
	return (0);
}

void	display(t_data *data)
{
	data->window->mlx = mlx_init();
	if (!data->window->mlx || !data->window->main)
		return ;
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
