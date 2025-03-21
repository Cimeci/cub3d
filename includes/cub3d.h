/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:22:41 by ncharbog          #+#    #+#             */
/*   Updated: 2025/03/21 14:56:37 by inowak--         ###   ########.fr       */
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

# define KEY_ESC 65307
# define SCREEN_HEIGHT 1080
# define SCREEN_WIDTH 1920

enum			e_id
{
	NO = 1,
	SO,
	WE,
	EA,
	F,
	C,
};

typedef struct s_player
{
	int			x;
	int			y;
	char or ;
	double		cam_height
}				t_player;

typedef  struct  s_line
{
	int  x; //the x coordinate of line relative to screen
	int  y; //the current pixel index of the line (along y axis)
	int  y0; //y start index of drawing texture
	int  y1; //y end index of drawing texture
	int  tex_x; //x coordinate of texture to draw
	int  tex_y; //y coordinate of texture to draw
} t_line;

typedef struct s_image
{
	double line_height;
	double line_length;
	double bits_per_pixel;
	
}	t_image;

typedef struct s_ray
{
	double pos_x;   // Position X du joueur
	double pos_y;   // Position Y du joueur
	double dir_x;   // Direction X du joueur
	double dir_y;   // Direction Y du joueur
	double plane_x; // Plan de la caméra X
	double plane_y; // Plan de la caméra Y
	double		move_speed;
	double		rot_speed;
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		wall_dist;
	double		wall_x;
	int			draw_start;
	int			draw_end;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			side;
	int			hit;
}				t_ray;

typedef struct s_window
{
	void		*win;
	void		*mlx;
	char		*n_txr;
	char		*s_txr;
	char		*w_txr;
	char		*e_txr;
	char		*f_color;
	char		*c_color;
}				t_window;

typedef struct s_data
{
	t_window	*window;
	t_list		*map_lst;
	char		**map;
	t_player	*player;
	t_ray		*ray;
	t_line		*line;
	t_image		*image;
}				t_data;

bool			is_space(char c);
bool			parsing(char *file, t_data *data);

void			print_error_exit(char *str, t_data *data);
void			init_data(t_data *data);
void			free_all(t_data *data);

bool			check_identifier(char *buf, t_data *data);
bool			pars_identifier(t_data *data);

bool			check_map(t_data *data, t_list *map);

bool			flood_fill(char **map, int y, int x);

void			display(t_data *data);

void			dda(t_data *data);
void 			init_ray(t_data *data);

#endif