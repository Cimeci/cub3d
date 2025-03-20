/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:00:20 by ncharbog          #+#    #+#             */
/*   Updated: 2025/03/19 17:10:20 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_rest_end(char *buf);
char	*ft_strdup2(char *s);
void	*ft_join_buf(char *buf, char *tmp, int count);
char	*ft_trim_line(char *buf);
int		ft_strlen2(char *s);
int		ft_check_n(char *s);
void	*ft_free(char *s1, char *s2);
char	*ft_strjoin2(char *s1, char *s2);

#endif
