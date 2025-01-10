/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:45:29 by ahusic            #+#    #+#             */
/*   Updated: 2025/01/10 18:28:25 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_newline(char *str)
{
	int	i;
	int	nl_count;

	i = 0;
	nl_count = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (nl_count > 0)
				return (printf("Error\nInvalid map/map info\n"), 0);
			nl_count++;
		}
		else
			nl_count = 0;
		i++;
	}
	return (1);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

int	file_to_map(int fd, t_data *map, char *line)
{
	char	*tmp;
	char	*map_str;

	if (!line)
		return (printf("Error\nMissing map\n"), 0);
	map_str = NULL;
	map->height = 0;
	while (line)
	{
		tmp = map_str;
		map_str = ft_strjoin_gnl(tmp, line);
		free(line);
		if (!map_str)
			return (printf("Error\nMemory allocation failed\n"), 0);
		map->height++;
		line = get_next_line(fd);
	}
	if (!check_newline(map_str))
		return (free(map_str), 0);
	map->map = ft_split(map_str, '\n');
	free(map_str);
	if (!map->map)
		return (printf("Error\nMemory allocation failed\n"), 0);
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
		if (data->no_texture)
			return (0);
		data->no_texture = ft_strdup(path);
	}
	else if (!ft_strncmp(id, "SO", 2))
	{
		if (data->so_texture)
			return (0);
		data->so_texture = ft_strdup(path);
	}
	else if (!ft_strncmp(id, "WE", 2))
	{
		if (data->we_texture)
			return (0);
		data->we_texture = ft_strdup(path);
	}
	else if (!ft_strncmp(id, "EA", 2))
	{
		if (data->ea_texture)
			return (0);
		data->ea_texture = ft_strdup(path);
	}
	return (1);
}
