/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:13:06 by ncharbog          #+#    #+#             */
/*   Updated: 2025/04/03 14:26:04 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (0);
	}
	init_data(&data);
	parsing(argv[1], &data);
	init_game(&data);
	display(&data);
	free_all(&data);
	return (0);
}
