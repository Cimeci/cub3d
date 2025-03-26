/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:53:31 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/26 18:50:01 by inowak--         ###   ########.fr       */
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
	img = data->window->main;
	// txt
	img->txt[NO] = mlx_xpm_file_to_image(win->mlx, win->n_txr, &width, &height);
	img->txt[SO] = mlx_xpm_file_to_image(win->mlx, win->s_txr, &width, &height);
	img->txt[WE] = mlx_xpm_file_to_image(win->mlx, win->w_txr, &width, &height);
	img->txt[EA] = mlx_xpm_file_to_image(win->mlx, win->e_txr, &width, &height);

	if (!img->txt[NO] || !img->txt[SO] || !img->txt[WE] || !img->txt[EA])
		print_error_exit("Failed to load textures", data);
	// addr
	img->addrtxt[NO] = mlx_get_data_addr(img->txt[NO], &img->bpp, &img->size_line, &img->endian);
    img->addrtxt[SO] = mlx_get_data_addr(img->txt[SO], &img->bpp, &img->size_line, &img->endian);
    img->addrtxt[WE] = mlx_get_data_addr(img->txt[WE], &img->bpp, &img->size_line, &img->endian);
    img->addrtxt[EA] = mlx_get_data_addr(img->txt[EA], &img->bpp, &img->size_line, &img->endian);
	img->txt[4] = NULL;
	img->addrtxt[4] = NULL;
}
