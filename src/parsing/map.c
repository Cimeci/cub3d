/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:29:47 by inowak--          #+#    #+#             */
/*   Updated: 2025/04/04 09:37:51 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_nb_player(t_list *map)
{
	int		i;
	int		nb;
	t_list	*tmp;

	i = 0;
	nb = 0;
	tmp = map;
	while (tmp)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (tmp->content[i] == 'N' || tmp->content[i] == 'S'
				|| tmp->content[i] == 'E' || tmp->content[i] == 'W')
				nb++;
			i++;
		}
		tmp = tmp->next;
	}
	if (nb != 1)
		return (false);
	return (true);
}

static char	*replace_line(t_data *data, char *content)
{
	char	*line;
	char	*add;
	int		i;

	i = 0;
	add = malloc(sizeof(char)
			* (data->map_width - (int)ft_strlen(content) + 1));
	if (!add)
		print_error_exit("Malloc error", data);
	while (i < (data->map_width - (int)ft_strlen(content)))
		add[i++] = '0';
	add[i] = '\0';
	line = ft_strjoin(content, add);
	free(add);
	free(content);
	return (line);
}

static void	format_map(t_data *data, t_list *map)
{
	t_list	*tmp;

	tmp = map;
	while (tmp)
	{
		if (tmp->content && data->map_width < (int)ft_strlen(tmp->content))
			data->map_width = ft_strlen(tmp->content);
		data->map_height++;
		tmp = tmp->next;
	}
	tmp = map;
	while (tmp)
	{
		if ((int)ft_strlen(tmp->content) < data->map_width)
			tmp->content = replace_line(data, tmp->content);
		tmp = tmp->next;
	}
}

static void	check_content(t_data *data, t_list *map)
{
	int		i;
	int		j;
	t_list	*tmp;

	j = 0;
	tmp = map;
	while (tmp)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (!is_valid_content(tmp->content[i]))
				print_error_exit("Map contains an invalid character", data);
			else if (is_valid_content(tmp->content[i]) == 2)
			{
				data->ray->pos_x = j;
				data->ray->pos_y = i;
				data->ray->ort = tmp->content[i];
			}
			i++;
		}
		j++;
		tmp = tmp->next;
	}
}

void	check_map(t_data *data, t_list *map)
{
	char	**newmap;

	check_content(data, map);
	replace_spaces(data->map_lst);
	format_map(data, data->map_lst);
	if (!check_nb_player(data->map_lst))
		print_error_exit("Must be one player", data);
	newmap = ft_convert_lst_to_tab(data->map_lst);
	if (!newmap)
		print_error_exit("Newmap clone", data);
	if (!flood_fill(newmap, data->ray->pos_y, data->ray->pos_x, 0))
	{
		ft_freetab(newmap);
		print_error_exit("Map not valid", data);
	}
	ft_freetab(newmap);
}
