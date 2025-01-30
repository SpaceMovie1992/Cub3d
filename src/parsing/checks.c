/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:11:19 by ahusic            #+#    #+#             */
/*   Updated: 2025/01/30 21:47:27 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_file_extension(char *filename)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (dot == NULL)
	{
		printf("Error\nNo file extension found\n");
		return (0);
	}
	if (ft_strncmp(dot, ".cub\0", 5) != 0)
	{
		printf("Error\n Invalid file extension\n");
		return (0);
	}
	return (1);
}

int	check_texture(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	check_color(char **rgb)
{
	if (!rgb[0] || !rgb[1] || !rgb[2] || !(rgb[2][0] == '\n'))
		return (0);
	if (!is_rgb(rgb[0]) || !is_rgb(rgb[1]) || !is_rgb(rgb[2]))
		return (0);
	if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255
		|| ft_atoi(rgb[1]) < 0 || ft_atoi(rgb[1]) > 255
		|| ft_atoi(rgb[2]) < 0 || ft_atoi(rgb[2]) > 255)
		return (0);
	return (1);
}

