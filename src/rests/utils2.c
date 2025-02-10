/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:09:21 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/06 22:19:37 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	calc_step_y(t_ray *ray, t_player *player)
{
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->player_y - ray->map_y * TILE_SIZE)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = ((ray->map_y + 1) * TILE_SIZE - player->player_y)
			* ray->delta_dist_y;
	}
}

void	copy_pixel(uint8_t *dst, uint8_t *src)
{
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	dst[3] = src[3];
}

void	scale_pixels(mlx_texture_t *scaled, mlx_texture_t *texture,
		int new_width, int new_height)
{
	int	x;
	int	y;
	int	src_index;
	int	dst_index;
	int	temp;

	y = 0;
	while (y < new_height)
	{
		x = 0;
		while (x < new_width)
		{
			temp = x * texture->width / new_width;
			src_index = ((y * texture->height / new_height)
					* texture->width + temp) * 4;
			dst_index = (y * new_width + x) * 4;
			copy_pixel(&scaled->pixels[dst_index],
				&texture->pixels[src_index]);
			x++;
		}
		y++;
	}
}

void cleanup_map(t_data *data)
{
    int i;

    if (data->map)
    {
        i = 0;
        while (data->map[i])
        {
            free(data->map[i]);
            i++;
        }
        free(data->map);
        data->map = NULL;
    }
}

void cleanup_texture_paths(t_data *data)
{
    if (data->no_texture_path)
        free(data->no_texture_path);
    if (data->so_texture_path)
        free(data->so_texture_path);
    if (data->we_texture_path)
        free(data->we_texture_path);
    if (data->ea_texture_path)
        free(data->ea_texture_path);
    data->no_texture_path = NULL;
    data->so_texture_path = NULL;
    data->we_texture_path = NULL;
    data->ea_texture_path = NULL;
}