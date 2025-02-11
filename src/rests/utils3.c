/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:20:48 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/11 18:25:00 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

uint32_t	get_tile_color(char tile)
{
	if (tile == '1')
		return (MINIMAP_WALL_COLOR);
	else if (tile == '0')
		return (MINIMAP_FLOOR_COLOR);
	else
		return (0x000000FF);
}

void	draw_tile(t_data *data, t_pos pos, char tile, int square_size)
{
	if (tile == ' ' || tile == '\0')
		draw_square(data, pos, square_size - 1, 0x000000FF);
	else
		draw_square(data, pos, square_size - 1,
			get_tile_color(tile));
}

int	get_max_width(t_data *data)
{
	int	i;
	int	len;
	int	max_width;

	i = 0;
	max_width = 0;
	while (i < data->height)
	{
		if (data->map[i] != NULL)
			len = ft_strlen(data->map[i]);
		else
			len = 0;
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

void	handle_minimap(t_data *data, int *cooldown, bool *minimap_toggle)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_M) && *cooldown == 0)
	{
		*minimap_toggle = !(*minimap_toggle);
		data->minimap.is_visible = *minimap_toggle;
		*cooldown = 10;
	}
	if (*cooldown > 0)
		(*cooldown)--;
}
