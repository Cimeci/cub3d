/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:29:47 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/20 13:43:43 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int	j;

	i = 0;
	j = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
		{
			if (file[i][j] == ' ')
				data->map[i][j] = '0';
			else
				data->map[i][j] = file[i][j];
			j++;
		}
		data->map[i][j] = '\0';
		i++;
	}
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
	int		len;
	int		j;
	char	**newmap;
	int		k;

	i = 0;
	j = 0;
	len = 0;
	printf("-----------------\n");
	printf(" CHECK ERROR MAP\n");
	printf("-----------------\n");
	data->map = malloc(sizeof(char *) * (cout_line_map(file) + 1));
	if (!data->map)
		return (false);
	data->map[cout_line_map(file)] = NULL;
	while (file[i])
	{
		j = 0;
		len = 0;
		while (is_space(file[i][j]))
			j++;
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
			len++;
			j++;
		}
		data->map[i] = malloc(sizeof(char) * (len + 1));
		if (!data->map[i])
			return (false);
		data->map[i][len] = '\0';
		i++;
	}
	printf("player: y: %d|x: %d\n", data->y, data->x);
	printf("-----------------\n");
	create_map(file, data);
	k = 0;
	while (data->map[k])
		printf("%s\n", data->map[k++]);
	printf("-----------------\n");
	newmap = ft_clone(data->map);
	if (!newmap)
		return (false);
	if (!flood_fill(newmap, data->y, data->x))
	{
		printf("Error\nMap not valid\n");
		ft_freetab(newmap);
		return (false);
	}
	printf("MAP\n");
	k = 0;
	while (newmap[k])
		printf("%s\n", newmap[k++]);
	ft_freetab(newmap);
	return (true);
}
