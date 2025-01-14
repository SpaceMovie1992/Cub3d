/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:29:58 by ahusic            #+#    #+#             */
/*   Updated: 2025/01/10 18:04:50 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	char_position_check(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (!ft_strchr("012NSEW ", data->map[i][j]))
				return (printf("Error\nInvalid character in map\n"), 0);
			if (ft_strchr("NSWE", data->map[i][j]))
			{
				if (data->pos_x != -1)
					return (printf("Error\nMultiple players found\n"), 0);
				data->pos_x = j;
				data->pos_y = i;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	map_check(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != '1' && data->map[i][j] != ' ')
			{
				if (i == 0 || !data->map[i + 1] || j == 0
					|| !data->map[i][j + 1] || data->map[i][j - 1] == ' '
					|| data->map[i][j + 1] == ' ' || data->map[i - 1][j] == ' '
					|| data->map[i + 1][j] == ' ')
					return (printf("Error\nMap is not enclosed\n"), 0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_valid_position(t_data *data, int x, int y)
{
	if (x <= 0 || x >= data->width - 1 || y <= 0 || y >= data->height - 1)
		return (0);
	if (data->map[y - 1][x] == ' ' || data->map[y + 1][x] == ' ' ||
		data->map[y][x - 1] == ' ' || data->map[y][x + 1] == ' ' ||
		data->map[y - 1][x] == '\0' || data->map[y + 1][x] == '\0' ||
		data->map[y][x - 1] == '\0' || data->map[y][x + 1] == '\0' ||
		x >= (int)ft_strlen(data->map[y - 1]))
		return (0);
	return (1);
}

int	save_position(t_data *data, int x, int y)
{
	if (data->pos_x >= 0 || data->pos_y >= 0)
		return (printf("Error\nMultiple player positions found\n"), 0);
	data->pos_x = x;
	data->pos_y = y;
	data->player_dir = data->map[x][y];
	return (1);
}

int	is_map_complete(t_data *data)
{
	if (!data->map || !data->no_texture || !data->so_texture
		|| !data->we_texture || !data->ea_texture || data->floor_color == -1
		|| data->ceiling_color == -1 || data->pos_x == -1)
		return (printf("Error\nIncomplete map data\n"), 0);
	return (1);
}
