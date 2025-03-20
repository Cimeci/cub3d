/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:00:02 by ncharbog          #+#    #+#             */
/*   Updated: 2025/03/19 17:10:36 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_free(char *s1, char *s2)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (NULL);
}

int	ft_strlen2(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_check_n(char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin2(char *buf, char *tmp)
{
	unsigned int		i;
	unsigned int		j;
	char				*dest;

	i = 0;
	j = 0;
	if (!buf && !tmp)
		return (0);
	dest = malloc((ft_strlen2(buf) + ft_strlen2(tmp) + 1) * sizeof(char));
	if (!dest)
		return (0);
	while (buf && buf[i])
	{
		dest[i] = buf[i];
		i++;
	}
	j = 0;
	while (tmp && tmp[j])
	{
		dest[i] = tmp[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
