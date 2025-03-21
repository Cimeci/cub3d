/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:44:10 by ncharbog          #+#    #+#             */
/*   Updated: 2025/03/21 13:33:03 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_list(t_list **head)
{
	t_list	*current;
	t_list	*next_node;

	current = *head;
	next_node = NULL;
	while (current)
	{
		next_node = current->next;
		free(current->content);
		current->content = NULL;
		free(current);
		current = next_node;
	}
	*head = NULL;
}

void	free_all(t_data *data)
{
	if (data->window->n_txr)
		free(data->window->n_txr);
	if (data->window->s_txr)
		free(data->window->s_txr);
	if (data->window->w_txr)
		free(data->window->w_txr);
	if (data->window->e_txr)
		free(data->window->e_txr);
	if (data->window->f_color)
		free(data->window->f_color);
	if (data->window->c_color)
		free(data->window->c_color);
	if (data->map)
		ft_freetab(data->map);
	if (data->player)
		free(data->player);
	if (data->map_lst)
		free_list(&data->map_lst);
	if (data->window)
		free(data->window);
}

void	print_error_exit(char *str, t_data *data)
{
	if (str)
		printf("Error\n%s\n", str);
	if (data)
		free_all(data);
	exit(EXIT_FAILURE);
}
