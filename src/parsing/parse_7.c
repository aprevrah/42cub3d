/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:57:23 by tmeniga@stu       #+#    #+#             */
/*   Updated: 2024/12/01 17:23:32 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

unsigned int	ft_to_int(char *str, unsigned int *i)
{
	unsigned int	nbr;

	nbr = 0;
	while ('0' <= str[*i] && str[*i] <= '9')
	{
		nbr = nbr * 10 + (str[*i] - '0');
		*i += 1;
	}
	return (nbr);
}


int		ft_strlen1(char const *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
char	*ft_strjoin1(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen1(s1) + ft_strlen1(s2) + 1;
	res = malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

void	remove_line(char *str, int i)
{
	int j;

	j = 0;
	while (str[i])
		str[j++] = str[i++];
	str[j] = '\0';
	j++;
	while (str[j])
    {
        str[j++] = '\0';
    }
}

char	*get_line(char *str)
{
	int		i;
	int		j;
	char	*line;
	
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	line[j] = '\0';
	remove_line(str, i);
	return (line);
}

char	*read_file(int fd)
{
	char buffer[2];
	char *result;
	char *temp;
	ssize_t bytes_read;

	result = NULL;
	temp = NULL;
	bytes_read = read(fd, buffer, 1);
	if (bytes_read < 0)
		return (NULL);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin1(result, buffer);
		if (!temp)
			return (free(result), NULL);
		free(result);
		result = temp;
		bytes_read = read(fd, buffer, 1);
	}
	if (bytes_read < 0)
		return (free(result), NULL);
	return (result);
}
