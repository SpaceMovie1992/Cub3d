/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:58:18 by ahusic            #+#    #+#             */
/*   Updated: 2025/01/30 19:30:55 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	map_parse(int fd, t_data *data, char *line)
{
	data->pos_x = -1;
	data->pos_y = -1;
	if (!file_to_map(fd, data, line))
		return (0);
	if (!char_position_check(data) || !map_check(data))
		return (0);
	if (data->pos_x == -1 || data->pos_y == -1)
		return (printf("Error\nNo player found\n"), 0);
	return (1);
}

int	texture_parse(char *content, t_data *data)
{
	char	**texture;
	char	*path;

	texture = ft_split(content, ' ');
	if (texture[1])
	{
		path = ft_strtrim(texture[1], " \t\n\r\v\f");
		if (texture[2] || !check_texture(path))
			return (free(path), free_2d_array(texture),
				printf("Error\nInvalid texture\n"), 0);
		if (!save_texture(data, texture[0], path))
			return (free(path), free_2d_array(texture), 0);
		free(path);
		path = NULL;
	}
	free_2d_array(texture);
	return (1);
}

int	color_parse(char *content, t_data *data, char type)
{
	char	**colors;
	int		rgb[3];

	colors = ft_split(content, ',');
	if (!check_color(colors))
		return (free_2d_array(colors), printf("Error\nInvalid color\n"), 0);
	rgb[0] = ft_atoi(colors[0]);
	rgb[1] = ft_atoi(colors[1]);
	rgb[2] = ft_atoi(colors[2]);
	if (type == 'f')
		data->floor_color = convert_rgb(rgb[0], rgb[1], rgb[2], 255);
	else
		data->ceiling_color = convert_rgb(rgb[0], rgb[1], rgb[2], 255);
	free_2d_array(colors);
	return (1);
}

int	save_content(char *content, t_data *data, int fd)
{
	while (content)
	{
		if (is_texture(content))
			if (!texture_parse(content, data))
				return (free(content), 0);
		if (*content == 'F')
			if (!color_parse(content + 2, data, 'f'))
				return (free(content), 0);
		if (*content == 'C')
			if (!color_parse(content + 2, data, 'c'))
				return (free(content), 0);
		if (!is_texture(content) && *content != 'F' && *content != 'C')
		{
			if (!map_parse(fd, data, content))
				return (0);
			break ;
		}
		free(content);
		content = skip_newline(fd);
	}
	return (1);
}
