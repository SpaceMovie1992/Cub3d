/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:45:29 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/06 18:02:28 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_newline(char *str)
{
	int	i;
	int	nl_count;
	int	in_map_section;

	in_map_section = 0;
	i = 0;
	nl_count = 0;
	while (str[i++])
	{
		if (str[i] == '\n')
		{
			if (in_map_section && nl_count > 0)
				return (0);
			nl_count++;
		}
		else
		{
			nl_count = 0;
			if (!in_map_section && (str[i] == '0' || str[i] == '1'
					|| str[i] == 'N' || str[i] == 'S' || str[i] == 'W'
					|| str[i] == 'E'))
				in_map_section = 1;
		}
	}
	return (1);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	int		should_free_s1;

	should_free_s1 = (s1 != NULL);
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
	{
		if (!should_free_s1)
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

int	file_to_map(int fd, t_data *map, char *line)
{
	char	*tmp;
	char	*map_str;
	int		line_len;

	if (!line || ft_strlen(line) <= 1)
		return (0);
	map_str = NULL;
	map->height = 0;
	map->width = 0;
	while (line)
	{
		if (ft_strlen(line) <= 1)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		line_len = ft_strlen(line);
		if (line[line_len - 1] == '\n')
			line_len--;
		map->width = (line_len > map->width) ? line_len : map->width;
		tmp = map_str;
		map_str = ft_strjoin_gnl(tmp, line);
		free(line);
		if (!map_str)
		{
			if (tmp)
				free(tmp);
			return (0);
		}
		map->height++;
		line = get_next_line(fd);
	}
	if (!check_newline(map_str))
		return (free(map_str), 0);
	map->map = ft_split(map_str, '\n');
	free(map_str);
	if (!map->map)
		return (0);
	return (1);
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	save_texture(t_data *data, char *id, char *path)
{
	char	*temp;

	if (!ft_strncmp(id, "NO", 2))
	{
		temp = ft_strdup(path);
		if (!temp)
			return (0);
		data->no_texture_path = temp;
	}
	else if (!ft_strncmp(id, "SO", 2))
	{
		temp = ft_strdup(path);
		if (!temp)
			return (0);
		data->so_texture_path = temp;
	}
	else if (!ft_strncmp(id, "WE", 2))
	{
		temp = ft_strdup(path);
		if (!temp)
			return (0);
		data->we_texture_path = temp;
	}
	else if (!ft_strncmp(id, "EA", 2))
	{
		temp = ft_strdup(path);
		if (!temp)
			return (0);
		data->ea_texture_path = temp;
	}
	return (1);
}
