/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallrender.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:46:43 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/06 17:57:30 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_ray_values(t_ray *ray, t_data *data, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->dir_x = cos(data->player.angle) - sin(data->player.angle) * camera_x;
	ray->dir_y = sin(data->player.angle) + cos(data->player.angle) * camera_x;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->map_x = (int)(data->player.player_x / TILE_SIZE);
	ray->map_y = (int)(data->player.player_y / TILE_SIZE);
}

static void	calc_step_and_side_dist(t_ray *ray, t_data *data)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.player_x / TILE_SIZE - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.player_x
				/ TILE_SIZE) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.player_y / TILE_SIZE - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.player_y
				/ TILE_SIZE) * ray->delta_dist_y;
	}
}

static int	perform_dda(t_ray *ray, t_data *data)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0 || ray->map_x >= data->width
			|| ray->map_y >= data->height)
			break ;
		if (data->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	return (side);
}

void	render_walls(t_data *data)
{
	t_ray	ray;
	t_wall	wall;
	int		x;
	int		side;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray_values(&ray, data, x);
		calc_step_and_side_dist(&ray, data);
		side = perform_dda(&ray, data);
		ray.wall_hit = side;
		calc_wall_height(&wall, &ray, data, side);
		draw_textured_line(data, &wall, &ray, x);
		x++;
	}
}

static mlx_texture_t	*load_scaled_texture(char *path)
{
	mlx_texture_t	*temp;
	mlx_texture_t	*scaled;

	temp = mlx_load_png(path);
	if (!temp)
		return (NULL);
	scaled = scale_texture(temp, TEXTURE_SIZE, TEXTURE_SIZE);
	mlx_delete_texture(temp);
	return (scaled);
}

bool	load_textures(t_data *data)
{
	if (!data->no_texture_path || !data->so_texture_path
		|| !data->we_texture_path || !data->ea_texture_path)
		return (false);
	data->no_texture = load_scaled_texture(data->no_texture_path);
	if (!data->no_texture)
		return (false);
	data->so_texture = load_scaled_texture(data->so_texture_path);
	if (!data->so_texture)
		return (cleanup_textures(data), false);
	data->we_texture = load_scaled_texture(data->we_texture_path);
	if (!data->we_texture)
		return (cleanup_textures(data), false);
	data->ea_texture = load_scaled_texture(data->ea_texture_path);
	if (!data->ea_texture)
		return (cleanup_textures(data), false);
	return (true);
}
