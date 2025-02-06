/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:29:58 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/06 18:01:34 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	set_player_pos(t_data *data, int i, int j)
{
	if (data->pos_x != -1)
		return (0);
	data->pos_x = j;
	data->pos_y = i;
	data->player_dir = data->map[i][j];
	return (1);
}

static int	is_valid_position(t_data *data, int i, int j, int width)
{
	if (i == 0 || i == data->height - 1 || j == 0 || j == width - 1)
		return (0);
	if (!data->map[i - 1] || !data->map[i + 1])
		return (0);
	return (data->map[i][j - 1] != ' ' && data->map[i][j + 1] != ' '
		&& data->map[i - 1][j] != ' ' && data->map[i + 1][j] != ' ');
}

int	map_check(t_data *data)
{
	int	i;
	int	j;
	int	width;

	if (!data->map)
		return (0);
	width = 0;
	while (data->map[0][width] && data->map[0][width] != '\n')
		width++;
	if (!check_width(data->map, width))
		return (0);
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (++j < width)
			if (data->map[i][j] != '1' && data->map[i][j] != ' '
				&& !is_valid_position(data, i, j, width))
				return (0);
	}
	return (1);
}

int	check_valid_position(t_data *data, int x, int y)
{
	if (x <= 0 || x >= data->width - 1 || y <= 0 || y >= data->height - 1)
		return (0);
	if (data->map[y - 1][x] == ' ' || data->map[y + 1][x] == ' '
		|| data->map[y][x - 1] == ' ' || data->map[y][x + 1] == ' '
		|| data->map[y - 1][x] == '\0' || data->map[y + 1][x] == '\0'
		|| data->map[y][x - 1] == '\0' || data->map[y][x + 1] == '\0'
		|| x >= (int)ft_strlen(data->map[y - 1]))
		return (0);
	return (1);
}

int	is_map_complete(t_data *data)
{
	if (!data->map || !data->no_texture || !data->so_texture
		|| !data->we_texture || !data->ea_texture || data->fc == -1
		|| data->cc == -1 || data->pos_x == -1)
		return (0);
	return (1);
}
