/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:11:19 by ahusic            #+#    #+#             */
/*   Updated: 2025/01/06 18:05:53 by ahusic           ###   ########.fr       */
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


// int	check_file_path(t_data *map, char *path)
// {
// 	char	buffer[1];
// 	ssize_t	read_result;

// 	if (!map || !path)
// 		return (printf("Error\nInvalid map or path\n"), 0);
// 	if ((map->fd = open(path, O_RDONLY)) < 0)
// 		return (printf("Error\nCannot open file\n"), 0);
// 	read_result = read(map->fd, buffer, 1);
// 	if (read_result <= 0)
// 	{
// 		close(map->fd);
// 		return (printf("Error\nFile is not readable\n"), map->fd = -1, 0);
// 	}
// 	close(map->fd);
// 	map->fd = open(path, O_RDONLY);
// 	map->path = ft_strdup(path);
// 	if (map->fd < 0 || !map->path)
// 	{
// 		if (map->fd >= 0)
// 			close(map->fd);
// 		return (map->fd = -1, 0);
// 	}
// 	return (1);
// }
