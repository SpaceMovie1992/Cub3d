/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:29:58 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/10 22:11:39 by ahusic           ###   ########.fr       */
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

int	map_check(t_data *data)
{
	int	i;
	int	j;
	int	len;

	if (!data->map)
		return (0);
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		len = ft_strlen(data->map[i]);
		while (data->map[i][++j])
		{
			if (data->map[i][j] == '0' || ft_strchr("NSEW", data->map[i][j]))
			{
				if (!check_valid_position(data, j, i))
					return (printf("Error\nMap is not properly closed\n"), 0);
			}
		}
	}
	return (1);
}

int	check_valid_position(t_data *data, int x, int y)
{
	if (y <= 0 || !data->map[y + 1] || x <= 0 
		|| x >= (int)ft_strlen(data->map[y]) - 1)
		return (0);
	if (x >= (int)ft_strlen(data->map[y - 1])
		|| x >= (int)ft_strlen(data->map[y + 1]))
		return (0);
	if (data->map[y - 1][x] == ' ' || data->map[y + 1][x] == ' '
		|| data->map[y][x - 1] == ' ' || data->map[y][x + 1] == ' ')
		return (0);
	return (1);
}

int	is_map_complete(t_data *data)
{
	if (!data->map || !data->no_texture || !data->so_texture
		|| !data->we_texture || !data->ea_texture || data->fc == -1
		|| data->cc == -1 || data->pos_x == -1)
		return (printf("Error\nMissing map elements\n"), 0);
	return (1);
}
