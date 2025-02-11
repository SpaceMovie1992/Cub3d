/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:08:38 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/11 18:33:06 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	draw_minimap_background(t_data *data, int map_pos_x, int map_pos_y,
		int square_size)
{
	t_pos	pos;
	int		width;
	int		height;
	int		i;
	int		j;

	width = data->background_width * square_size + 10;
	height = data->height * square_size + 10;
	i = -5;
	while (i < width)
	{
		j = -5;
		while (j < height)
		{
			pos.x = map_pos_x + i;
			pos.y = map_pos_y + j;
			mlx_put_pixel(data->img, pos.x, pos.y, 0x222222FF);
			j++;
		}
		i++;
	}
}

static void	draw_map_tiles(t_data *data, int map_pos_x, int map_pos_y,
		int square_size)
{
	int		x;
	int		y;
	t_pos	pos;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (!data->map[y] || x >= (int)ft_strlen(data->map[y]))
			{
				x++;
				continue ;
			}
			pos.x = map_pos_x + (x * square_size);
			pos.y = map_pos_y + (y * square_size);
			draw_tile(data, pos, data->map[y][x], square_size);
			x++;
		}
		y++;
	}
}

static void	draw_player_direction(t_data *data, int player_x, int player_y,
		int line_length)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < line_length)
	{
		x = player_x + (int)(cos(data->player.angle) * i);
		y = player_y + (int)(sin(data->player.angle) * i);
		mlx_put_pixel(data->img, x, y, 0x00FF00FF);
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	int		square_size;
	int		map_pos_x;
	int		map_pos_y;
	t_pos	player_pos;

	if (!data->minimap.is_visible)
		return ;
	square_size = MINIMAP_TILE_SIZE;
	map_pos_x = MINIMAP_PADDING;
	map_pos_y = MINIMAP_PADDING;
	data->background_width = get_max_width(data);
	draw_minimap_background(data, map_pos_x, map_pos_y, square_size);
	draw_map_tiles(data, map_pos_x, map_pos_y, square_size);
	player_pos.x = map_pos_x + (int)(data->player.player_x / TILE_SIZE
			* square_size) - 2;
	player_pos.y = map_pos_y + (int)(data->player.player_y / TILE_SIZE
			* square_size) - 2;
	draw_square(data, player_pos, 4, 0xFF0000FF);
	player_pos.x += 2;
	player_pos.y += 2;
	draw_player_direction(data, player_pos.x, player_pos.y, square_size);
}
