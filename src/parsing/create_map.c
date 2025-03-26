/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:29:47 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/26 13:56:39 by inowak--         ###   ########.fr       */
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

static void	replace_spaces(t_list *map)
{
	int	i;

	i = 0;
	while (map)
	{
		i = 0;
		while (map->content[i])
		{
			if (map->content[i] == ' ')
				map->content[i] = '0';
			i++;
		}
		map = map->next;
	}
}

char	**ft_convert_lst_to_tab(t_list *map)
{
	int		i;
	char	**table;
	t_list	*tmp;

	i = 0;
	table = malloc(sizeof(char *) * (ft_lstsize(map) + 1));
	if (!table)
		return (NULL);
	tmp = map;
	while (tmp)
	{
		table[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	table[i] = NULL;
	return (table);
}

void	format_map(t_data *data, t_list *map)
{
	t_list	*tmp;
	char	*add;
	char	*line;
	int		i;

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
		{
			add = malloc(sizeof(char) * (data->map_width - (int)ft_strlen(tmp->content) + 1));
			if (!add)
				return ;
			i = 0;
			while (i < (data->map_width - (int)ft_strlen(tmp->content)))
			{
				add[i] = '0';
				i++;
			}
			add[i] = '\0';
			line = ft_strjoin(tmp->content, add);
			free(add);
			free(tmp->content);
			tmp->content = line;
		}
		tmp = tmp->next;
	}
	printf("width: %d| height: %d\n", data->map_width, data->map_height);
}

bool	check_map(t_data *data, t_list *map)
{
	int		i;
	int		j;
	t_list	*tmp;
	char	**newmap;
	int		k;

	tmp = map;
	printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\nF: %d\nC: %d\n",
		data->window->n_txr, data->window->s_txr, data->window->e_txr,
		data->window->w_txr, data->window->f_color, data->window->c_color);
	printf("-----------------\n");
	i = 0;
	j = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (tmp->content[i] != '0' && tmp->content[i] != '1'
				&& tmp->content[i] != ' ' && tmp->content[i] != 'N'
				&& tmp->content[i] != 'S' && tmp->content[i] != 'E'
				&& tmp->content[i] != 'W')
				return (false);
			else if (tmp->content[i] == 'N' || tmp->content[i] == 'S'
				|| tmp->content[i] == 'E' || tmp->content[i] == 'W')
			{
				data->player->y = j;
				data->player->x = i;
				data->ray->pos_x = j;
				data->ray->pos_y = i;
				data->player->or = tmp->content[i];
				printf("player: x = %d| y = %d| or = %c\n", data->player->x,
					data->player->y, data->player->or);
			}
			i++;
		}
		j++;
		tmp = tmp->next;
	}
	replace_spaces(data->map_lst);
	format_map(data, data->map_lst);
	newmap = ft_convert_lst_to_tab(data->map_lst);
	if (!newmap)
		print_error_exit("Newmap clone", data);
	if (!check_nb_player(data->map_lst))
	{
		ft_freetab(newmap);
		print_error_exit("Must be one player", data);
	}
	k = 0;
	printf("MAP\n");
	printf("-----------------\n");
	while (newmap[k])
		printf("%s\n", newmap[k++]);
	if (!flood_fill(newmap, data->player->y, data->player->x))
	{
		ft_freetab(newmap);
		print_error_exit("Map not valid", data);
	}
	k = 0;
	printf("-----------------\n");
	printf("floodfill MAP\n");
	printf("-----------------\n");
	while (newmap[k])
		printf("%s\n", newmap[k++]);
	ft_freetab(newmap); // garder newmap ?
	return (true);
}
