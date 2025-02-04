/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:11:19 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/04 12:20:03 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
