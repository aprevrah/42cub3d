/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:00:43 by aprevrha          #+#    #+#             */
/*   Updated: 2023/12/14 23:14:11 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*split_nl(char **str)
{
	char		*free_me;
	char		*line;
	char		*p_first_nl;

	free_me = *str;
	p_first_nl = gnl_ft_strchr(*str, '\n');
	*str = gnl_ft_strdup(p_first_nl + 1);
	if (!*str)
		return (free(free_me), free_me = NULL, NULL);
	p_first_nl[1] = '\0';
	line = gnl_ft_strdup(free_me);
	if (!line)
		return (free(*str), free(free_me), free_me = NULL, NULL);
	return (free(free_me), free_me = NULL, line);
}

static char	*read_to_nl(int fd, char *str)
{
	char		*buffer;
	ssize_t		bytes_read;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (free(str), str = NULL, NULL);
	buffer[0] = '\0';
	bytes_read = 1;
	while (!gnl_ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(str), str = NULL, NULL);
		buffer[bytes_read] = '\0';
		if (!str)
			str = gnl_ft_strdup(buffer);
		else
			str = gnl_ft_strjoin(str, buffer);
		if (!str)
			return (free(buffer), NULL);
	}
	return (free(buffer), str);
}

char	*get_next_line(int fd)
{
	static char	*str[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!str[fd] || !gnl_ft_strchr(str[fd], '\n'))
		str[fd] = read_to_nl(fd, str[fd]);
	if (!str[fd] || str[fd][0] == 0)
		return (free(str[fd]), str[fd] = NULL, NULL);
	else if (gnl_ft_strchr(str[fd], '\n'))
	{
		line = split_nl(&(str[fd]));
		if (!line)
			return (free(str[fd]), str[fd] = NULL, NULL);
		return (line);
	}
	line = gnl_ft_strdup(str[fd]);
	if (!line)
		return (free(str[fd]), str[fd] = NULL, NULL);
	return (free(str[fd]), str[fd] = NULL, line);
}
