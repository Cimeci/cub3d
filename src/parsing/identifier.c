/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:26:49 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/20 14:21:57 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	compare_identifier(char *id, int len)
{
	if (len > 2)
		return (0);
	if (!ft_strncmp(id, "NO", len))
		return (NO);
	else if (!ft_strncmp(id, "SO", len))
		return (SO);
	else if (!ft_strncmp(id, "WE", len))
		return (WE);
	else if (!ft_strncmp(id, "EA", len))
		return (EA);
	else if (!ft_strncmp(id, "F", len))
		return (F);
	else if (!ft_strncmp(id, "C", len))
		return (C);
	return (0);
}

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

bool	check_colors(char *str, int it)
{
	int		i;
	char	number[10];

	i = 0;
	if (it == 3)
		return (true);
	while (str[i] && (str[i] >= '0' && str[i] <= '9') && i < 10)
	{
		number[i] = str[i];
		i++;
	}
	number[i] = '\0';
	if (i == 0 || ft_atoi(number) > 255 || atoi(number) < 0)
		return (false);
	if ((it == 2 && !str[i]) || str[i] == ',')
	{
		if (it == 2 && !str[i])
			return (true);
		if (it < 2 && str[i])
			i++;
		return (check_colors(str + i, it + 1));
	}
	return (false);
}

static void	assign_texture(int id, char *buf, t_data *data)
{
	char *path;

	path = take_path(buf);
	if (!path)
		return ;
	if (id == NO)
		data->n_txr = path;
	else if (id == SO)
		data->s_txr = path;
	else if (id == WE)
		data->w_txr = path;
	else if (id == EA)
		data->e_txr = path;
	else if (id == F || id == C)
	{
		if (!check_colors(path, 0))
		{
			free(path);
			print_error_exit("RGB color is invalid", data);
		}
		if (id == F)
			data->f_color = path;
		else if (id == C)
			data->c_color = path;
	}
}

bool	check_identifier(char *buf, t_data *data)
{
	int	i;
	int	len;
	int	id;

	i = 0;
	len = 0;
	while (buf[i] && is_space(buf[i]))
		i++;
	if (!buf[i] || buf[i] == '\n')
		return (false);
	while (buf[i + len] && !is_space(buf[i + len]))
		len++;
	id = compare_identifier(buf + i, len);
	if (!id)
		return (false);
	i += len;
	while (buf[i] && is_space(buf[i]))
		i++;
	assign_texture(id, buf + i, data);
	return (true);
}
