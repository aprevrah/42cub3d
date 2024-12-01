/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:57:23 by tmeniga@stu       #+#    #+#             */
/*   Updated: 2024/12/01 18:49:20 by tmeniga@stu      ###   ########.fr       */
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
char *ft_substr1(char *str, int start, int len) 
{
    char *substr;
    int i = 0;

    if (!str || start < 0 || len < 0)
        return NULL;

    substr = malloc(sizeof(char) * (len + 1));
    if (!substr)
        return NULL;

    while (i < len && str[start + i]) 
	{
        substr[i] = str[start + i];
        i++;
    }
    substr[i] = '\0';
    return substr;
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

char *remove_line(char *str, int i) 
{
    char *new_str;
    int len;

    len = ft_strlen1(str);
    if (i >= len) { // If no characters remain to copy
        free(str);
        return NULL;
    }

    new_str = ft_substr(str, i, len - i);
    if (!new_str) { // Allocation failed
        free(str);
        return NULL;
    }

    free(str); // Free the old string
    return new_str;
}

char *get_line(char **str) 
{
    int i = 0;
    char *line;

    if (!str || !(*str))
        return NULL;

    // Find newline or end of string
    while ((*str)[i] && (*str)[i] != '\n')
        i++;

    // Include the newline
    if ((*str)[i] == '\n')
        i++;

    // Allocate memory for the line
    line = malloc(sizeof(char) * (i + 1));
    if (!line)
        return NULL;

    // Copy the line into the new string
    for (int j = 0; j < i; j++)
        line[j] = (*str)[j];
    line[i] = '\0';

    // Remove the line from the original string
    char *new_str = remove_line(*str, i);
	// free(*str);
	*str = new_str;

    return line;
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
