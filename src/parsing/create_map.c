/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:29:47 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/20 17:49:29 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool check_nb_player(char **map)
{
	int i= 0;
	int j = 0;
	int nb = 0;

	while (map[i][j])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				nb++;
			j++;
		}
		i++;
	}
	if (nb != 1)
		return (false);
	return (true);
}

static int	cout_line_map(char **file)
{
	int	i;
	
	i = 0;
	while (file[i])
		i++;
	return (i);
}

static void	create_map(char **file, t_data *data)
{
	int	i;
	int k;
	int	j;

	k = 0;
	i = 0;
	j = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j] != '\0')
		{
			if (file[i][j] == ' ')
				data->map[k][j] = '0';
			else
				data->map[k] = file[i];
			j++;
		}
		k++;
		i++;
	}
	data->map[k] = NULL;
}

char	**ft_clone(char **map)
{
	char	**newmap;
	int		len;

	len = 0;
	while (map[len])
		len++;
	newmap = malloc(sizeof(char *) * (len + 1));
	if (!newmap)
		return (NULL);
	len = 0;
	while (map[len])
	{
		newmap[len] = ft_strdup(map[len]);
		if (!newmap[len])
   			return (NULL);
		len++;
	}
	newmap[len] = NULL;
	return (newmap);
}

bool	check_map(char **file, t_data *data)
{
	int		i;
	int		j;
	char	**newmap;
	int		k;

	i = 0;
	j = 0;
	while (file[i] && file[i][0] == '\0')
		i++;
	printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\nF: %s\nC: %s\n", data->n_txr, data->s_txr, data->e_txr, data->w_txr, data->f_color, data->c_color);
	printf("-----------------\n");
	printf(" CHECK ERROR MAP\n");
	printf("-----------------\n");
	printf("%d\n", cout_line_map(file));
	data->map = malloc(sizeof(char *) * (cout_line_map(file) + 1));
	if (!data->map)
		return (false);
	while (file[i])
	{
		j = 0;
		// while (is_space(file[i][j]))
		// 	j++;
		while (file[i][j])
		{
			if (file[i][j] != '0' && file[i][j] != '1' && file[i][j] != ' '
				&& file[i][j] != 'N' && file[i][j] != 'S' && file[i][j] != 'E'
				&& file[i][j] != 'W')
				return (false);
			else if (file[i][j] == 'N' || file[i][j] == 'S' || file[i][j] == 'E'
				|| file[i][j] == 'W')
			{
				data->y = i;
				data->x = j;
			}
			j++;
		}
		data->map[i] = malloc(sizeof(char) * (j + 1));
		if (!data->map[i])
			return (false);
		i++;
	}
	printf("player: y: %d|x: %d\n", data->y, data->x);
	printf("-----------------\n");
	create_map(file, data);
	k = 0;
	while (data->map[k])
		printf("|%s|\n", data->map[k++]);
	newmap = ft_clone(data->map);
	if (!newmap)
		print_error_exit("Newmap clone", data);
	if (!check_nb_player(data->map))
	{
		ft_freetab(newmap);
		print_error_exit("Must be one player", data);
	}
	if (!flood_fill(newmap, data->y, data->x))
	{
		ft_freetab(newmap);
		print_error_exit("Map not valid", data); // free newmap
	}
	printf("-----------------\n");
	printf("MAP\n");
	printf("-----------------\n");
	k = 0;
	while (newmap[k])
		printf("%s\n", newmap[k++]);
	ft_freetab(newmap);
	return (true);
}
