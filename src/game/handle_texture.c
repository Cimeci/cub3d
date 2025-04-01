/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:53:31 by inowak--          #+#    #+#             */
/*   Updated: 2025/04/01 09:54:04 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texture(t_data *data)
{
	t_img		*img;
	t_window	*win;
	int			width;
	int			height;

	win = data->window;
	img = data->window->txr;
	// txt
	img[NO].img = mlx_xpm_file_to_image(win->mlx, win->n_txr, &width, &height);
	img[SO].img = mlx_xpm_file_to_image(win->mlx, win->s_txr, &width, &height);
	img[WE].img = mlx_xpm_file_to_image(win->mlx, win->w_txr, &width, &height);
	img[EA].img = mlx_xpm_file_to_image(win->mlx, win->e_txr, &width, &height);
	img[4].img = NULL;

	if (!img[NO].img || !img[SO].img || !img[WE].img || !img[EA].img)
		print_error_exit("Failed to load textures", data);
	// addr
	img[NO].addr = mlx_get_data_addr(img[NO].img, &img[NO].bpp, &img[NO].size_line, &img[NO].endian);
    img[SO].addr = mlx_get_data_addr(img[SO].img, &img[SO].bpp, &img[SO].size_line, &img[SO].endian);
    img[WE].addr = mlx_get_data_addr(img[WE].img, &img[WE].bpp, &img[WE].size_line, &img[WE].endian);
    img[EA].addr = mlx_get_data_addr(img[EA].img, &img[EA].bpp, &img[EA].size_line, &img[EA].endian);
	img[4].addr = NULL;
}
