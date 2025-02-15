/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:11:19 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/10 22:48:38 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_file_extension(char *filename)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (dot == NULL || ft_strncmp(dot, ".cub\0", 5) != 0)
		return (printf("Error\nInvalid file extension\n"), 0);
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
	int	r;
	int	g;
	int	b;

	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (0);
	if (!is_rgb(rgb[0]) || !is_rgb(rgb[1]) || !is_rgb(rgb[2]))
		return (0);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (1);
}

int	char_position_check(t_data *data)
{
	int	i;
	int	j;

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
			if (!ft_strchr("01NSEW ", data->map[i][j]))
				return (printf("Error\nInvalid character in map\n"), 0);
			if (ft_strchr("NSWE", data->map[i][j])
				&& ((data->pos_x != -1 && data->pos_y != -1)
					|| !set_player_pos(data, i, j)))
				return (printf("Error\nMultiple players in map\n"), 0);
		}
	}
	if (data->pos_x == -1 || data->pos_y == -1)
		return (printf("Error\nNo player in map\n"), 0);
	return (1);
}
