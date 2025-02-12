/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:45:29 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/12 18:36:23 by mstefano         ###   ########.fr       */
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
	int		should_free_s1;
	char	*empty_str;

	should_free_s1 = (s1 != NULL);
	if (!s1)
	{
		empty_str = malloc(sizeof(char) * 1);
		if (!empty_str)
			return (NULL);
		empty_str[0] = '\0';
		return (join_strings(empty_str, s2, 1));
	}
	return (join_strings(s1, s2, should_free_s1));
}

int	file_to_map(int fd, t_data *map, char *line)
{
	char	*map_str;
	int		result;

	if (!line || ft_strlen(line) <= 1)
		return (0);
	map_str = NULL;
	map->height = 0;
	map->width = 0;
	while (line)
	{
		result = line_process(&map_str, line, map);
		if (result == 0)
			return (0);
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
	if (!ft_strncmp(id, "NO", 2))
	{
		if (!set_texture_path(&data->no_texture_path, path))
			return (0);
	}
	else if (!ft_strncmp(id, "SO", 2))
	{
		if (!set_texture_path(&data->so_texture_path, path))
			return (0);
	}
	else if (!ft_strncmp(id, "WE", 2))
	{
		if (!set_texture_path(&data->we_texture_path, path))
			return (0);
	}
	else if (!ft_strncmp(id, "EA", 2))
	{
		if (!set_texture_path(&data->ea_texture_path, path))
			return (0);
	}
	return (1);
}
