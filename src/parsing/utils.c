/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:34:20 by ahusic            #+#    #+#             */
/*   Updated: 2025/01/10 18:42:09 by ahusic           ###   ########.fr       */
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
	while (line && ft_strlen(line) <= 1)
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
	return ((line[0] == 'N' && line[0] == 'O')
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

int	is_rgb(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
