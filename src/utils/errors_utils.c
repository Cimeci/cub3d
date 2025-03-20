/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:44:10 by ncharbog          #+#    #+#             */
/*   Updated: 2025/03/20 14:25:07 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(t_data *data)
{
	if (data->n_txr)
		free(data->n_txr);
	if (data->s_txr)
		free(data->s_txr);
	if (data->w_txr)
		free(data->w_txr);
	if (data->e_txr)
		free(data->e_txr);
	if (data->f_color)
		free(data->f_color);
	if (data->c_color)
		free(data->c_color);
	if (data->map)
		ft_freetab(data->map);
}

void	print_error_exit(char *str, t_data *data)
{
	if (str)
		printf("Error\n%s\n", str);
	if (data)
		free_all(data);
	exit(EXIT_FAILURE);
}
