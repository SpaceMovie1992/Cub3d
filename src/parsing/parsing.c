/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:58:18 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/02 14:39:57 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int map_parse(int fd, t_data *data, char *line)
{
    data->pos_x = -1;
    data->pos_y = -1;
    data->player_dir = '\0';
    
    if (!file_to_map(fd, data, line))
    {
        printf("file_to_map failed\n");
        return (0);
    }
    if (!char_position_check(data))
    {
        printf("char_position_check failed\n");
        return (0);
    }
    if (!map_check(data))
    {
        printf("map_check failed\n");
        return (0);
    }
    return (1);
}

int texture_parse(char *content, t_data *data)
{
    char    **texture;
    char    *path;
	
    texture = ft_split(content, ' ');
    if (texture[1])
    {
        path = ft_strtrim(texture[1], " \t\n\r\v\f");
        if (texture[2] || !check_texture(path))
            return (free(path), free_2d_array(texture), 0);
        if (!save_texture(data, texture[0], path))
            return (free(path), free_2d_array(texture), 0);
        free(path);
        path = NULL;
    }
    else
        return (free_2d_array(texture), 0);
    free_2d_array(texture);
    return (1);
}

int	color_parse(char *content, t_data *data, char type)
{
    char    **colors;
    int     rgb[3];

    colors = ft_split(content, ',');
    if (!colors)
        return (0);

    if (!check_color(colors))
        return (free_2d_array(colors), 0);    
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
        if (ft_strlen(content) <= 1 || content[0] == '#' || content[0] == '\n')
        {
            free(content);
            content = skip_newline(fd);
            continue;
        }
        if (is_texture(content))
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
            break;
        }
        else
            return (printf("Error\nInvalid map/map info\n"), free(content), 0);
        free(content);
        content = skip_newline(fd);
    }
    return (1);
}
