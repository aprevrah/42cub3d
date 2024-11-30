#include "../include/cub3d.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 12
# endif

char	*get_next_line44(int fd, int x);

int		check_for_nl44(char *buffer);

char	*ft_strjoin44(char *s1, char *s2);

size_t	ft_strlen44(const char *str);

char	*get_res44(char *s);

char	*get_remainder44(char *buffer);

char	*ft_read44(int fd, char *buffer);

void	*ft_calloc44(size_t count, size_t size);

void	ft_bzero44(void *str, size_t n);

void	*ft_calloc44(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero44(ptr, count * size);
	return (ptr);
}

void	ft_bzero44(void *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)str + i) = '\0';
		i++;
	}
}

int	check_for_nl44(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen44(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin44(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*res;

	len = ft_strlen44(s1) + ft_strlen44(s2) + 1;
	res = malloc(sizeof(char) * len);
	if (!res || !s1 || !s2)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1[j] != '\0')
		res[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}

char	*get_next_line44(int fd, int x)
{
	static char	*buffer;
	char		*res;


	if (buffer && x)
		return (free(buffer), buffer = NULL, NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read44(fd, buffer);
	if (!buffer)
	{
		return (NULL);
	}
	res = get_res44(buffer);
	buffer = get_remainder44(buffer);
	return (res);
}

char	*ft_read44(int fd, char *buffer)
{
	char			*temp;
	long long int	bytes_read;

	if (!buffer)
		buffer = ft_calloc44(1, 1);
	temp = ft_calloc44(BUFFER_SIZE + 1, sizeof(char));
	if (!temp)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp);
			free(buffer);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		buffer = ft_strjoin44(buffer, temp);
		if (check_for_nl44(buffer))
			break ;
	}
	free(temp);
	return (buffer);
}

char	*get_res44(char *buffer)
{
	int		i;
	char	*res;

	i = 0;
	if (!buffer[0])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	res = ft_calloc44(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
	{
		res[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n' && buffer[i])
		res[i++] = '\n';
	return (res);
}

char	*get_remainder44(char *buffer)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	res = ft_calloc44((ft_strlen44(buffer) - i + 1), sizeof(char));
	if (!res)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		res[j++] = buffer[i++];
	free(buffer);
	return (res);
}