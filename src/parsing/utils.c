/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:34:20 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/01 18:11:49 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	convert_rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

char	*skip_newline(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && (ft_strlen(line) == 0 || line[0] == '#'))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

int	is_texture(char *line)
{
	if (!line || ft_strlen(line) < 2)
		return (0);
	return ((line[0] == 'N' && line[1] == 'O')
		|| (line[0] == 'S' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E')
		|| (line[0] == 'E' && line[1] == 'A'));
}

int	is_color(char *content)
{
	if (!ft_strncmp(content, "F", 2))
		return (1);
	if (!ft_strncmp(content, "C", 2))
		return (1);
	return (0);
}

int is_rgb(char *str)
{
    int i;

    i = 0;
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    if (!str[i])
        return (0);
    while (str[i] && str[i] != '\n' && str[i] != ' ' && str[i] != '\t')
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
        i++;
    return (str[i] == '\0');
}

void init_data(t_data *data)
{
    data->mlx = NULL;
    data->img = NULL;
    data->map = NULL;
    data->no_texture = NULL;
    data->so_texture = NULL;
    data->we_texture = NULL;
    data->ea_texture = NULL;
    data->path = NULL;
    data->player_dir = '\0';
    data->fd = -1;
    data->height = 0;
    data->width = 0;
    data->floor_color = 0;
    data->ceiling_color = 0;
    data->pos_x = -1;
    data->pos_y = -1;
    data->dir_x = 0;
    data->dir_y = 0;
    data->plane_x = 0;
    data->plane_y = 0;
    data->player.player_x = 0;
    data->player.player_y = 0;
    data->player.angle = 0;
    data->player.fov = FOV;
    data->player.rotation = 0;
    data->player.l_r = 0;
    data->player.u_d = 0;
}
