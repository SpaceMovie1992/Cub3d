/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:29:58 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/01 18:22:56 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int char_position_check(t_data *data)
{
    int i;
    int j;

    if (!data || !data->map)
    {
        printf("Error: NULL map data\n");
        return (0);
    }
    data->pos_x = -1;
    data->pos_y = -1;
    data->player_dir = '\0';
    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if (!ft_strchr("012NSEW ", data->map[i][j]))
            {
                printf("Error: Invalid character '%c' at [%d][%d]\n", 
                       data->map[i][j], i, j);
                return (0);
            }
            if (ft_strchr("NSWE", data->map[i][j]))
            {
                if (data->pos_x != -1)
                {
                    printf("Error: Multiple players found\n");
                    return (0);
                }
                data->pos_x = j;
                data->pos_y = i;
                data->player_dir = data->map[i][j];
                printf("Player found at [%d][%d] facing %c\n", i, j, data->player_dir);
            }
            j++;
        }
        i++;
    }
    if (data->pos_x == -1 || data->pos_y == -1)
    {
        printf("Error: No player found in map\n");
        return (0);
    }
    return (1);
}

int map_check(t_data *data)
{
    int i;
    int j;
    int width;
    char *line;

    if (!data->map)
        return (printf("Error\nMap is NULL\n"), 0);
    line = data->map[0];
    width = 0;
    while (line[width] && line[width] != '\n')
        width++;
    i = 0;
    while (data->map[i])
    {
        int line_len = 0;
        while (data->map[i][line_len] && data->map[i][line_len] != '\n')
            line_len++;
        if (line_len != width)
            return (printf("Error\nMap lines have different lengths (%d != %d at line %d)\n", 
                         line_len, width, i), 0);
        j = 0;
        while (j < width)
        {   
            if (data->map[i][j] != '1' && data->map[i][j] != ' ')
            {
                if (i == 0 || i == data->height - 1 || j == 0 || j == width - 1)
                    return (printf("Error\nMap is not enclosed at [%d][%d]\n", i, j), 0);
                if (!data->map[i - 1] || !data->map[i + 1] ||
                    data->map[i][j - 1] == ' ' ||
                    data->map[i][j + 1] == ' ' ||
                    data->map[i - 1][j] == ' ' ||
                    data->map[i + 1][j] == ' ')
                    return (printf("Error\nMap is not properly enclosed at [%d][%d]\n", i, j), 0);
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
