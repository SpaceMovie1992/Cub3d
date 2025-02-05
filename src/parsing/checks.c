/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:11:19 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/05 20:21:45 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_file_extension(char *filename)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (dot == NULL)
		return (0);
	if (ft_strncmp(dot, ".cub\0", 5) != 0)
		return (0);
	return (1);
}

int check_texture(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (0);
    close(fd);
    return (1);
}

int check_color(char **rgb)
{
    if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
        return (0);
    if (!is_rgb(rgb[0]) || !is_rgb(rgb[1]) || !is_rgb(rgb[2]))
        return (0);
    int r = ft_atoi(rgb[0]);
    int g = ft_atoi(rgb[1]);
    int b = ft_atoi(rgb[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (0);
    return (1);
}

int check_width(char **map, int width)
{
    int i;
    int len;

    i = 0;
    while (map[i])
    {
        len = 0;
        while (map[i][len] && map[i][len] != '\n')
            len++;
        if (len != width)
            return (0);
        i++;
    }
    return (1);
}

int char_position_check(t_data *data)
{
    int i;
    int j;

    if (!data || !data->map)
        return (0);
    data->pos_x = -1;
    data->pos_y = -1;
    data->player_dir = '\0';
    i = -1;
    while (data->map[++i])
    {
        j = -1;
        while (data->map[i][++j])
        {
            if (!ft_strchr("012NSEW ", data->map[i][j]))
                return (0);
            if (ft_strchr("NSWE", data->map[i][j]) && !set_player_pos(data, i, j))
                return (0);
        }
    }
    return (data->pos_x != -1 && data->pos_y != -1);
}
