/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:22:02 by ncharbog          #+#    #+#             */
/*   Updated: 2025/04/02 11:06:27 by ncharbog         ###   ########.fr       */
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

static void	extract_map(t_data *data, int fd)
{
	char	*buf;
	t_list	*node;

	while (1)
	{
		buf = get_next_line(fd);
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
	}
}

static void	extract_file(char *filename, t_data *data)
{
	int		is_id;
	int		fd;
	char	*buf;

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
				print_error_exit("Invalid identifier", data);
			}
			is_id++;
		}
		free(buf);
	}
	extract_map(data, fd);
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
	if (!data->map || !data->map[0])
		print_error_exit("Invalid assignation map", NULL);
	return (true);
}
