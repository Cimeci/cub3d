/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:22:41 by ncharbog          #+#    #+#             */
/*   Updated: 2025/03/20 16:35:45 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/GNL/get_next_line.h"
# include "../lib/libft/libft.h"
# include "../lib/minilibx/mlx.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#define KEY_ESC 65307
#define SCREEN_HEIGHT 1080
#define SCREEN_WIDTH 1920

enum		e_id
{
	NO = 1,
	SO,
	WE,
	EA,
	F,
	C,
};

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;


typedef struct s_data
{
	void	*win;
	void	*mlx;
	char	*n_txr;
	char	*s_txr;
	char	*w_txr;
	char	*e_txr;
	char	*f_color;
	char	*c_color;
	char	**map;
	int		x;
	int		y;


	double posX;       // Position X du joueur
    double posY;       // Position Y du joueur
    double dirX;       // Direction X du joueur
    double dirY;       // Direction Y du joueur
    double planeX;     // Plan de la caméra X
    double planeY;     // Plan de la caméra Y
    double moveSpeed;
    double rotSpeed;
}			t_data;

bool		is_space(char c);
bool		parsing(char *file, t_data *data);

void		print_error_exit(char *str, t_data *data);
void		init_data(t_data *data);
void		free_all(t_data *data);

bool		check_identifier(char *buf, t_data *data);
bool		pars_identifier(t_data *data);

bool		check_map(char **file, t_data *data);

bool		flood_fill(char **map, int y, int x);

void		display(t_data *data);

void		raycasting(t_data *data);

#endif