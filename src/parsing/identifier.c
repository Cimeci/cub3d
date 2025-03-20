/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:26:49 by inowak--          #+#    #+#             */
/*   Updated: 2025/03/20 06:37:31 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_all_digit(char *nb)
{
	int	i;

	i = 0;
	while (nb[i])
	{
		if (!ft_isdigit(nb[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	check_identifier_path(t_data *data)
{
	int	fd;

	fd = open(data->n_txr, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	fd = open(data->s_txr, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	fd = open(data->e_txr, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	fd = open(data->w_txr, O_RDONLY);
	if (fd < 0)
		return (false);
	close (fd);
	return (true);
}

bool	pars_identifier(t_data *data)
{
	char	**f_colors;
	char	**c_colors;
	int		i;

	i = 0;
	f_colors = ft_split(data->f_color, ',');
	c_colors = ft_split(data->c_color, ',');
	if (ft_strlentab(f_colors) != 3 || ft_strlentab(c_colors) != 3)
		return (ft_freetab(f_colors) && ft_freetab(c_colors));
	while (f_colors[i] && c_colors[i])
	{
		if (!is_all_digit(f_colors[i]) || !is_all_digit(c_colors[i]))
			return (ft_freetab(f_colors) && ft_freetab(c_colors));
		if (ft_atoi(f_colors[i]) < 0 || ft_atoi(f_colors[i]) > 255
			|| ft_atoi(c_colors[i]) < 0 || ft_atoi(c_colors[i]) > 255)
			return (ft_freetab(f_colors) && ft_freetab(c_colors));
		i++;
	}
	// condition pour le check des textures, a activer quand on aura des fichiers textures
	if (!check_identifier_path(data))
		;
	return (true);
}

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

static char	*take_path(char *buf)
{
	char	*path;
	int		len;

	len = 0;
	while (buf[len] && !is_space(buf[len]))
		len++;
	path = ft_substr(buf, 0, len);
	if (!path)
		return (NULL);
	return (path);
}

static void	assign_texture(int id, char *buf, t_data *data)
{
	char	*path;

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
	else if (id == F)
		data->f_color = path;
	else if (id == C)
		data->c_color = path;
	printf("id: %d |path: %s\n", id, path);
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
