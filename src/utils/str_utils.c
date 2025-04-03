/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:04:37 by ncharbog          #+#    #+#             */
/*   Updated: 2025/04/03 12:01:09 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*take_path(char *buf)
{
	char	*path;
	int		len;

	len = ft_strlen(buf) - 1;
	while (len > 0 && is_space(buf[len]))
		len--;
	path = ft_substr(buf, 0, len + 1);
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

char	*only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str)
	{
		if (is_space(*str))
			str++;
		else
			return (str);
	}
	return (str);
}
