/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:22:41 by ncharbog          #+#    #+#             */
/*   Updated: 2025/04/02 11:14:36 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/GNL/get_next_line.h"
# include "../lib/libft/libft.h"
# include "../lib/minilibx/mlx.h"
# include "structs_enums.h"
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
# define KEY_SHIFT 65505
# define KEY_C 99

# define SCREEN_HEIGHT 500
# define SCREEN_WIDTH 800

// keys.c
int				close_window(t_data *data);
int				key_press_move(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);

// move.c
void			move_player(t_data *data);

// raycasting.c
void			dda(t_data *data);

// textures.c
void			init_texture(t_data *data);

// window.c
void			display(t_data *data);

// errors_utils.c
void			free_all(t_data *data);
void			end_game(t_data *data);
void			print_error_exit(char *str, t_data *data);

// init.c
void			init_game(t_data *data);
void			init_data(t_data *data);
void			init_raycasting(t_ray *ray, int x);

// time.c
double			get_time_in_ms(void);
void			set_fps(t_data *data);

// str_utils.c
char			*take_path(char *buf);
bool			is_space(char c);
void			suppnl(char *line);
char			**ft_convert_lst_to_tab(t_list *map);
void			replace_spaces(t_list *map);

// flood_fill.c
bool			flood_fill(char **map, int y, int x);

// identifier.c
bool			check_identifier(char *buf, t_data *data);

// map.c
void			check_map(t_data *data, t_list *map);

// parsing.c
int				is_valid_content(char c);
bool			parsing(char *file, t_data *data);

#endif