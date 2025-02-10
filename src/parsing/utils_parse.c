/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:36:49 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/06 22:02:54 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	process_line(char *content, t_data *data, int fd)
{
	if (!ft_strncmp(content, "NO ", 3) || !ft_strncmp(content, "SO ", 3)
		|| !ft_strncmp(content, "WE ", 3) || !ft_strncmp(content, "EA ", 3))
	{
		if (!texture_parse(content, data))
			return (0);
	}
	else if (*content == 'F')
	{
		if (!color_parse(content + 2, data, 'f'))
			return (0);
	}
	else if (*content == 'C')
	{
		if (!color_parse(content + 2, data, 'c'))
			return (0);
	}
	else if (content[0] == '1' || content[0] == ' ')
	{
		if (!map_parse(fd, data, content))
			return (0);
		return (2);
	}
	else
		return (0);
	return (1);
}

int	save_content(char *content, t_data *data, int fd)
{
	int	result;

	while (content)
	{
		if (ft_strlen(content) <= 1 || content[0] == '#' || content[0] == '\n')
		{
			free(content);
			content = get_next_line(fd);
			continue ;
		}
		result = process_line(content, data, fd);
		if (result == 0)
			return (free(content), 0);
		if (result == 2)
			break ;
		free(content);
		content = get_next_line(fd);
	}
	return (1);
}

char *join_strings(char *s1, char *s2, int should_free_s1)
{
    char    *str;
    size_t  i;
    size_t  j;

    str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!str)
    {
        if (should_free_s1)
            free(s1);
        return (NULL);
    }
    i = -1;
    while (s1[++i])
        str[i] = s1[i];
    j = 0;
    while (s2[j])
        str[i++] = s2[j++];
    str[i] = '\0';
    if (should_free_s1)
        free(s1);
    return (str);
}
int	line_process(char **map_str, char *line, t_data *map)
{
	char	*tmp;
	int		line_len;

	if (ft_strlen(line) <= 1)
	{
		free(line);
		return (2);
	}
	line_len = ft_strlen(line);
	if (line[line_len - 1] == '\n')
		line_len--;
	if (line_len > map->width)
		map->width = line_len;
	tmp = *map_str;
	*map_str = ft_strjoin_gnl(tmp, line);
	free(line);
	if (!*map_str)
	{
		if (tmp)
			free(tmp);
		return (0);
	}
	map->height++;
	return (1);
}

int set_texture_path(char **texture_path, char *path)
{
    char *temp;

    if (*texture_path)
        free(*texture_path);
    temp = ft_strdup(path);
    if (!temp)
        return (0);
    *texture_path = temp;
    return (1);
}
