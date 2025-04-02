/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:26:49 by inowak--          #+#    #+#             */
/*   Updated: 2025/04/02 16:11:04 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	compare_identifier(char *id, int len)
{
	if (len > 2)
		return (6);
	if (!ft_strncmp(id, "NO", len) && len == 2)
		return (NO);
	else if (!ft_strncmp(id, "SO", len) && len == 2)
		return (SO);
	else if (!ft_strncmp(id, "WE", len) && len == 2)
		return (WE);
	else if (!ft_strncmp(id, "EA", len) && len == 2)
		return (EA);
	else if (!ft_strncmp(id, "F", len) && len == 1)
		return (F);
	else if (!ft_strncmp(id, "C", len) && len == 1)
		return (C);
	return (0);
}

static bool	check_colors(char *str, int it)
{
	int		i;
	char	number[10];

	i = 0;
	if (it == 3 && only_spaces(str))
		return (true);
	else if (it == 3 && !only_spaces(str))
		return (false);
	while (str[i] && (str[i] >= '0' && str[i] <= '9') && i < 10)
	{
		number[i] = str[i];
		i++;
	}
	number[i] = '\0';
	if (i == 0 || ft_atoi(number) > 255 || ft_atoi(number) < 0)
		return (false);
	if (it == 2 || (str[i] == ',' && it < 3))
	{
		if (it < 2 && str[i])
			i++;
		return (check_colors(str + i, it + 1));
	}
	return (false);
}

static void	convert_colors(t_data *data, char *path, int id)
{
	char	**tmp;
	int		r;
	int		g;
	int		b;
	int		color;

	tmp = ft_split(path, ',');
	r = ft_atoi(tmp[0]);
	g = ft_atoi(tmp[1]);
	b = ft_atoi(tmp[2]);
	color = (r << 16) | (g << 8) | b;
	if (id == F)
		data->window->f_color = color;
	else if (id == C)
		data->window->c_color = color;
	ft_freetab(tmp);
}

static bool	assign_texture(int id, char *buf, t_data *data)
{
	char	*path;

	path = take_path(buf);
	if (!path)
		return (false);
	if (id == NO)
		data->window->n_txr = path;
	else if (id == SO)
		data->window->s_txr = path;
	else if (id == WE)
		data->window->w_txr = path;
	else if (id == EA)
		data->window->e_txr = path;
	if (id == F || id == C)
	{
		if (!check_colors(path, 0))
		{
			free(path);
			return (false);
		}
		convert_colors(data, path, id);
		free(path);
	}
	return (true);
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
	if (!buf[i])
		return (true);
	while (buf[i + len] && !is_space(buf[i + len]))
		len++;
	id = compare_identifier(buf + i, len);
	if (data->id_tab[id] == true)
		return (false);
	else
		data->id_tab[id] = true;
	if (id == 6)
		return (false);
	i += len;
	while (buf[i] && is_space(buf[i]))
		i++;
	if (!assign_texture(id, buf + i, data))
		return (false);
	return (true);
}
