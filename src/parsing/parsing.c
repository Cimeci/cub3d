/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:22:02 by ncharbog          #+#    #+#             */
/*   Updated: 2025/03/24 14:45:25 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_space(char c)
{
	if ((c >= 7 && c <= 13) || c == 32)
		return (true);
	return (false);
}

static void	suppnl(char *line)
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

static void	extract_file(char *filename, t_data *data)
{
	int		is_id;
	int		fd;
	char	*buf;
	t_list	*node;

	is_id = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error_exit("Failed to access to the .cub file", data);
	while (is_id < 6)
	{
		buf = get_next_line(fd);
		if (buf[0] != '\n')
		{
			suppnl(buf);
			if (!buf || !check_identifier(buf, data))
			{
				free(buf);
				print_error_exit("Invalid identifier", data); // free buffer
			}
			is_id++;
		}
		free(buf);
	}
	while (1)
	{
		buf = get_next_line(fd);
		if (buf && buf[0] != '\n')
		{
			suppnl(buf);
			node = ft_lstnew(buf);
			if (!node)
				print_error_exit("Malloc error", data); // free buffer
			ft_lstadd_back(&data->map_lst, node);
			break ;
		}
		free(buf);
	}
	while (1)
	{
		buf = get_next_line(fd);
		suppnl(buf);
		if (!buf)
			break ;
		node = ft_lstnew(buf);
		if (!node)
			print_error_exit("Malloc error", data); // free buffer
		ft_lstadd_back(&data->map_lst, node);
	}
}

static void	check_extension(char *file)
{
	if (!file || ft_strlen(file) < 5)
		print_error_exit("Invalid .cub file", NULL);
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4))
		print_error_exit("Invalid .cub file", NULL);
}

bool	parsing(char *file, t_data *data)
{
	check_extension(file);
	extract_file(file, data);
	check_map(data, data->map_lst);
	data->map = ft_convert_lst_to_tab(data->map_lst);
	return (true);
}
