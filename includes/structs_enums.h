/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_enums.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:13:28 by ncharbog          #+#    #+#             */
/*   Updated: 2025/04/03 09:23:52 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_ENUMS_H
# define STRUCTS_ENUMS_H

# include "../lib/libft/libft.h"
# include <stdbool.h>

enum			e_id
{
	SO,
	NO,
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
	SHIFT,
};

typedef struct s_ray
{
	double		pos_x;
	double		pos_y;
	char		ort;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
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
	int			tex_x;
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
	t_img		*txr;
	bool		keypress[8];
}				t_window;

typedef struct s_fps
{
	double		start_time;
	double		old_time;
	double		time;
	double		frame_time;
}				t_fps;

typedef struct s_data
{
	int			map_width;
	int			map_height;
	char		**map;
	int			fd;
	bool		id_tab[6];
	t_window	*window;
	t_list		*map_lst;
	t_ray		*ray;
	t_fps		*fps;
}				t_data;

#endif