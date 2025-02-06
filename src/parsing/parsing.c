/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:58:18 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/06 18:00:12 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	map_parse(int fd, t_data *data, char *line)
{
	data->pos_x = -1;
	data->pos_y = -1;
	data->player_dir = '\0';
	if (!file_to_map(fd, data, line))
		return (0);
	if (!char_position_check(data))
		return (0);
	if (!map_check(data))
		return (0);
	return (1);
}

int	texture_parse(char *content, t_data *data)
{
	char	**texture;
	char	*path;
	int		result;

	texture = ft_split(content, ' ');
	if (!texture || !texture[0] || !texture[1])
	{
		free_2d_array(texture);
		return (0);
	}
	path = ft_strtrim(texture[1], " \t\n\r\v\f");
	if (!check_texture(path))
	{
		free(path);
		free_2d_array(texture);
		return (0);
	}
	result = save_texture(data, texture[0], path);
	free(path);
	free_2d_array(texture);
	return (result);
}

int	color_parse(char *content, t_data *data, char type)
{
	char	**colors;
	int		rgb[3];

	colors = ft_split(content, ',');
	if (!colors)
		return (0);
	if (!check_color(colors))
		return (free_2d_array(colors), 0);
	rgb[0] = ft_atoi(colors[0]);
	rgb[1] = ft_atoi(colors[1]);
	rgb[2] = ft_atoi(colors[2]);
	if (type == 'f')
		data->fc = (rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF;
	else
		data->cc = (rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF;
	free_2d_array(colors);
	return (1);
}

int	save_content(char *content, t_data *data, int fd)
{
	while (content)
	{
		if (ft_strlen(content) <= 1 || content[0] == '#' || content[0] == '\n')
		{
			free(content);
			content = get_next_line(fd);
			continue ;
		}
		if (!ft_strncmp(content, "NO ", 3) || !ft_strncmp(content, "SO ", 3)
			|| !ft_strncmp(content, "WE ", 3) || !ft_strncmp(content, "EA ", 3))
		{
			if (!texture_parse(content, data))
				return (free(content), 0);
		}
		else if (*content == 'F')
		{
			if (!color_parse(content + 2, data, 'f'))
				return (free(content), 0);
		}
		else if (*content == 'C')
		{
			if (!color_parse(content + 2, data, 'c'))
				return (free(content), 0);
		}
		else if (content[0] == '1' || content[0] == ' ')
		{
			if (!map_parse(fd, data, content))
				return (0);
			break ;
		}
		else
			return (free(content), 0);
		free(content);
		content = get_next_line(fd);
	}
	return (1);
}

int	save_position(t_data *data, int x, int y)
{
	if (data->pos_x >= 0 || data->pos_y >= 0)
		return (0);
	data->pos_x = x;
	data->pos_y = y;
	data->player_dir = data->map[x][y];
	return (1);
}
