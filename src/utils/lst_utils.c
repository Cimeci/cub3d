/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:45:41 by ncharbog          #+#    #+#             */
/*   Updated: 2025/04/02 14:48:51 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	replace_spaces(t_list *map)
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
