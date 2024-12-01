/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:47:38 by tmeniga@stu       #+#    #+#             */
/*   Updated: 2024/11/30 21:08:58 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_only_numeric_and_2_comma(char *str, int i)
{
	int	count;

	count = 0;
	if (!str || str[i] == '\0')
		return (0);
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ',' && str[i] != ' '
			&& str[i] != '\t' && str[i] != '\r' && str[i] != '\v'
			&& str[i] != '\f' && str[i] != '\n')
		{
			return (0);
		}
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count == 2);
}

int	gc_error_check(char *s)
{
	if (count_words(s) != 2)
		return (err("Error: color line needs 2 arguments\n"), 1);
	if (s[1] && s[1] != ' ')
		return (err("Error: missing space after identifier\n"), 1);
	if (!is_only_numeric_and_2_comma(s, 1))
		return (err("Error: syntax error in color line\n"), 1);
	return (0);
}

int	get_color(char *s, unsigned int *color)
{
	unsigned int	i;
	t_color_value	color_value;

	i = 0;
	if (gc_error_check(s))
		return (1);
	skip_until(s, &i, WHITESPACE, true);
	if (!skip_until(s, &i, WHITESPACE, false))
		return (1);
	color_value.r = ft_to_int(s, &i);
	if (s[i] != ',')
		return (1);
	i++;
	skip_until(s, &i, WHITESPACE, false);
	color_value.g = ft_to_int(s, &i);
	if (s[i] != ',')
		return (1);
	i++;
	skip_until(s, &i, WHITESPACE, false);
	color_value.b = ft_to_int(s, &i);
	if (color_value.r > 255 || color_value.g > 255 || color_value.b > 255)
		return (err("Error: color values too high\n"), 1);
	*color = (color_value.r << 16) | (color_value.g << 8) | color_value.b;
	return (0);
}

int	get_key(unsigned int *i, char *s, char **path)
{
	unsigned int	start;

	if (count_words(s) != 2)
		return (err("Error: texture line needs 2 arguments\n"), 1);
	if (s[*i + 2] && s[*i + 2] != ' ')
		return (err("Error: missing space after identifier\n"), 1);
	skip_until(s, i, WHITESPACE, true);
	if (!skip_until(s, i, WHITESPACE, false))
		return (err("Error: Unable to parse: "), err(s), 1);
	start = *i;
	skip_until(s, i, "\n", true);
	if (*path)
		return (err("Error: Duplicate config: "), err(s), 1);
	*path = ft_substr(s, start, *i - start);
	if (!*path)
		return (err("Error: Malloc failed."), 1);
	trim_spaces_at_end(*path);
	return (0);
}

int	key_val(char *line, t_texture_data *texture_data)
{
	unsigned int	i;

	i = 0;
	skip_until(line, &i, WHITESPACE, false);
	if (line[i] == '\0')
		return (2);
	else if (!ft_strncmp(&line[i], "NO", 2))
		return (get_key(&i, line, &texture_data->path_no));
	else if (!ft_strncmp(&line[i], "EA", 2))
		return (get_key(&i, line, &texture_data->path_ea));
	else if (!ft_strncmp(&line[i], "SO", 2))
		return (get_key(&i, line, &texture_data->path_so));
	else if (!ft_strncmp(&line[i], "WE", 2))
		return (get_key(&i, line, &texture_data->path_we));
	else if (!ft_strncmp(&line[i], "C", 1))
		return (get_color(&line[i], &texture_data->col_c));
	else if (!ft_strncmp(&line[i], "F", 1))
		return (get_color(&line[i], &texture_data->col_f));
	return (err("Error: Unable to parse: "), err(line), 1);
}
