/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:34:20 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/05 20:13:52 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	convert_rgb(int r, int g, int b, int a)
{
	return (r << 0 | g << 12 | b << 24 | a);
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

int is_texture(char *line)
{
    if (!ft_strncmp(line, "NO ", 3))
        return (1);
    if (!ft_strncmp(line, "SO ", 3))
        return (1);
    if (!ft_strncmp(line, "WE ", 3))
        return (1);
    if (!ft_strncmp(line, "EA ", 3))
        return (1);
    return (0);
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
