/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:04:37 by ncharbog          #+#    #+#             */
/*   Updated: 2025/04/02 10:08:34 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*take_path(char *buf)
{
	char	*path;
	int		len;

	len = ft_strlen(buf);
	while (len > 0 && is_space(buf[len]))
		len--;
	path = ft_substr(buf, 0, len);
	if (!path)
		return (NULL);
	return (path);
}

bool	is_space(char c)
{
	if ((c >= 7 && c <= 13) || c == 32)
		return (true);
	return (false);
}

void	suppnl(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
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
