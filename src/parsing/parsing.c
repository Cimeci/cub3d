/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:22:02 by ncharbog          #+#    #+#             */
/*   Updated: 2025/03/20 14:30:57 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_space(char c)
{
	if ((c >= 7 && c <= 13) || c == 32)
		return (true);
	return (false);
}

static int	count_line(char *file)
{
	int		fd;
	char	*line;
	int		len;

	len = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		len++;
		free(line);
	}
	close(fd);
	return (len);
}

static char	*suppnl(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (ft_substr(line, 0, ft_strlen(line) - 1));
		i++;
	}
	return (ft_strdup(line));
}

static char	**copy_file(char *filename)
{
	int		fd;
	int		i;
	int		len;
	char	*line;
	char	**file;

	i = 0;
	len = count_line(filename);
	if (!len)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	file = malloc(sizeof(char *) * (len + 1));
	if (!file)
		return (NULL);
	while (i < len)
	{
		line = get_next_line(fd);
		file[i] = suppnl(line);
		i++;
		free(line);
	}
	file[i] = NULL;
	close(fd);
	return (file);
}

static void	extract_identifiers(char **file, t_data *data, int *i, int *is_id)
{
	while (file[*i] && *is_id < 6)
	{
		if (file[*i][0] == '\0')
		{
			(*i)++;
			continue ;
		}
		if (!check_identifier(file[*i], data))
			print_error_exit("Invalid identifier", data);
		(*is_id)++;
		(*i)++;
	}
}

static bool	extract_file(char *filename, t_data *data)
{
	char	**file;
	int		i;
	int		is_id;

	i = 0;
	is_id = 0;
	file = copy_file(filename);
	if (!file)
		print_error_exit("Failed to access to the .cub file", data);
	extract_identifiers(file, data, &i, &is_id); // free file
	if (!pars_identifier(data))
		print_error_exit("Identifier input false", data); // free file
	if (!check_map(file + i, data))
	{
		ft_freetab(file);
		return (false);
	}
	ft_freetab(file);
	return (true);
}

static void	check_extension(char *file)
{
	if (!file || ft_strlen(file) < 5)
		print_error_exit("Invalid .cub file", NULL);
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4))
		print_error_exit("Invalid .cub file", NULL);
}

bool parsing(char *file, t_data *data)
{
	check_extension(file);
	copy_file(file, data);
	return (true);
}
