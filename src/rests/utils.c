/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:14:55 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/10 18:28:11 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_scene_wrapper(void *param)
{
	t_draw_params	*params;

	params = (t_draw_params *)param;
	if (!params || !params->data || !params->img)
		return ;
	draw_scene(params->data, params->img);
}

void	init_ray(t_data *data, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->dir_x = cos(data->player.angle) - sin(data->player.angle) * camera_x;
	ray->dir_y = -sin(data->player.angle) - cos(data->player.angle) * camera_x;
	ray->map_x = (int)(data->player.player_x / TILE_SIZE);
	ray->map_y = (int)(data->player.player_y / TILE_SIZE);
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

void	cleanup_textures(t_data *data)
{
	if (data->no_texture)
		mlx_delete_texture(data->no_texture);
	if (data->we_texture)
		mlx_delete_texture(data->we_texture);
}

void	draw_square(t_data *data, t_pos pos, int size, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(data->img, pos.x + i, pos.y + j, color);
			j++;
		}
		i++;
	}
}

int	is_valid_pos(t_data *data, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= data->width || map_y < 0 || map_y >= data->height)
		return (0);
	if (data->map[map_y][map_x] == '1')
		return (0);
	return (1);
}
