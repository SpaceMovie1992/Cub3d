/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:58:18 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/06 21:45:35 by ahusic           ###   ########.fr       */
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

int	save_position(t_data *data, int x, int y)
{
	if (data->pos_x >= 0 || data->pos_y >= 0)
		return (0);
	data->pos_x = x;
	data->pos_y = y;
	data->player_dir = data->map[x][y];
	return (1);
}
