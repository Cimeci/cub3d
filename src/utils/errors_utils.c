/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:44:10 by ncharbog          #+#    #+#             */
/*   Updated: 2025/04/02 14:42:23 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	finish_file(char *buf, int fd)
{
	while (buf)
	{
		free(buf);
		buf = get_next_line(fd);
	}
}

static void	free_list(t_list **head)
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
	if (data->map)
		ft_freetab(data->map);
	if (data->map_lst)
		free_list(&data->map_lst);
	if (data->window->txr)
		free(data->window->txr);
	if (data->window->main)
		free(data->window->main);
	if (data->window)
		free(data->window);
	if (data->ray)
		free(data->ray);
	if (data->fps)
		free(data->fps);
}

void	end_game(t_data *data)
{
	int	i;

	i = 0;
	if (data->window->main && data->window->main->img)
		mlx_destroy_image(data->window->mlx, data->window->main->img);
	while (i < 5)
	{
		if (data->window->mlx && data->window->txr[i].img)
			mlx_destroy_image(data->window->mlx, data->window->txr[i].img);
		i++;
	}
	if (data->window->win)
		mlx_destroy_window(data->window->mlx, data->window->win);
	if (data->window->mlx)
	{
		mlx_destroy_display(data->window->mlx);
		free(data->window->mlx);
	}
}

void	print_error_exit(char *str, t_data *data)
{
	if (str)
		printf("Error\n%s\n", str);
	if (data)
	{
		end_game(data);
		free_all(data);
	}
	exit(EXIT_FAILURE);
}
