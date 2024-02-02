/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:17:20 by aprevrha          #+#    #+#             */
/*   Updated: 2023/12/14 23:14:17 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define MAX_FD 1024

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char			*get_next_line(int fd);
unsigned long	gnl_ft_strlen(const char *s);
char			*gnl_ft_strjoin(char *s1, char *s2);
char			*gnl_ft_strchr(const char *s, int c);
char			*gnl_ft_strdup(char const *s1);

#endif