/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:22:41 by ncharbog          #+#    #+#             */
/*   Updated: 2025/03/26 14:13:30 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/GNL/get_next_line.h"
# include "../lib/libft/libft.h"
# include "../lib/minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 100
# define KEY_D 97
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
// # define SCREEN_HEIGHT 1080
// # define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 500
# define SCREEN_WIDTH 800
# define WALL_MARGIN 0.3

enum			e_id
{
	NO = 1,
	SO,
	WE,
	EA,
	F,
	C,
};

enum			e_key
{
	START,
	W,
	S,
	A,
	D,
	RA,
	LA,
};

typedef struct s_player
{
	int			x;
	int			y;
	char or ;
}				t_player;

typedef struct s_ray
{
	double pos_x;   // Position X du joueur
	double pos_y;   // Position Y du joueur
	double dir_x;   // Direction X du joueur
	double dir_y;   // Direction Y du joueur
	double plane_x; // Plan de la caméra X
	double plane_y; // Plan de la caméra Y
	double		camera_x;
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
	double		perp_wall_dist;
	int			draw_start;
	int			draw_end;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			side;
	int			hit;
	int			line_height;
	int			color;
}				t_ray;

typedef struct s_img
{
	int			*pixel_addr;
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct s_window
{
	void		*win;
	void		*mlx;
	char		*n_txr;
	char		*s_txr;
	char		*w_txr;
	char		*e_txr;
	int			f_color;
	int			c_color;
	t_img		*main;
	bool		keypress[7];
}				t_window;

typedef struct s_fps
{
	time_t		start_time;
	time_t		old_time;
	time_t		time;
	double		frame_time;
}				t_fps;

typedef struct s_data
{
	int			map_width;
	int			map_height;
	char		**map;
	t_window	*window;
	t_list		*map_lst;
	t_player	*player;
	t_ray		*ray;
	t_fps		*fps;
}				t_data;

bool			is_space(char c);
bool			parsing(char *file, t_data *data);

void			print_error_exit(char *str, t_data *data);
void			free_all(t_data *data);

void			init_data(t_data *data);
void			init_ray(t_data *data);
void			init_game(t_data *data);

bool			check_identifier(char *buf, t_data *data);
bool			pars_identifier(t_data *data);

bool			check_map(t_data *data, t_list *map);
char			**ft_convert_lst_to_tab(t_list *map);

bool			flood_fill(char **map, int y, int x);

void			display(t_data *data);
void			clear_window(t_data *data);
int				ft_raycasting(t_data *data);

void			dda(t_data *data);

time_t			get_time_in_ms(void);
void			set_fps(t_data *data);

#endif