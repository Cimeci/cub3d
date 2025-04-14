/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:22:02 by ncharbog          #+#    #+#             */
/*   Updated: 2025/04/14 16:17:45 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_content(char c)
{
	if (c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'E'
		&& c != 'S' && c != 'W')
		return (0);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (2);
	return (1);
}

static void	extract_map(t_data *data, char *buf)
{
	t_list	*node;

	while (1)
	{
		buf = get_next_line(data->fd);
		if (!buf)
			print_error_exit("No map was found", data);
		if (buf && buf[0] != '\n')
			break ;
		free(buf);
	}
	while (1)
	{
		suppnl(buf);
		if (!buf)
			break ;
		node = ft_lstnew(buf);
		if (!node)
		{
			free(buf);
			print_error_exit("Malloc error", data);
		}
		ft_lstadd_back(&data->map_lst, node);
		buf = get_next_line(data->fd);
	}
}

static void	extract_file(char *filename, t_data *data)
{
	int		is_id;
	char	*buf;

	is_id = 0;
	data->fd = open(filename, O_RDONLY);
	if (data->fd < 0 || open(filename, __O_DIRECTORY) > 0)
		print_error_exit("Failed to access to the .cub file", data);
	while (is_id < 6)
	{
		buf = get_next_line(data->fd);
		if (!buf)
			print_error_exit("Failed to access to the .cub file", data);
		if (buf[0] != '\n')
		{
			suppnl(buf);
			if (!buf || !check_identifier(buf, data))
			{
				finish_file(buf, data->fd);
				print_error_exit("Invalid identifier", data);
			}
			is_id++;
		}
		free(buf);
	}
	extract_map(data, buf);
}

static void	check_extension(t_data *data, char *file)
{
	if (!file || ft_strlen(file) < 5)
		print_error_exit("Invalid .cub file", data);
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4))
		print_error_exit("Invalid .cub file", data);
}

bool	parsing(char *file, t_data *data)
{
	check_extension(data, file);
	extract_file(file, data);
	close(data->fd);
	check_map(data, data->map_lst);
	data->map = ft_convert_lst_to_tab(data->map_lst);
	if (!data->map || !data->map[0])
		print_error_exit("Invalid assignation map", NULL);
	return (true);
}
