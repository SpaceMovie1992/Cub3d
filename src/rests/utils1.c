/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:51:46 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/11 19:42:12 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	handle_rotation(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.angle += ROTATION_SPEED;
		if (data->player.angle > 2 * M_PI)
			data->player.angle -= 2 * M_PI;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.angle -= ROTATION_SPEED;
		if (data->player.angle < 0)
			data->player.angle += 2 * M_PI;
	}
}

void	calc_wall_height(t_wall *wall, t_ray *ray, t_data *data, int side)
{
	if (side == 0)
		ray->distance = (ray->map_x - data->player.player_x / TILE_SIZE + (1
					- ray->step_x) / 2) / ray->dir_x;
	else
		ray->distance = (ray->map_y - data->player.player_y / TILE_SIZE + (1
					- ray->step_y) / 2) / ray->dir_y;
	wall->height = (int)(SCREEN_HEIGHT / ray->distance);
	wall->draw_start = -wall->height / 2 + SCREEN_HEIGHT / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->height / 2 + SCREEN_HEIGHT / 2;
	if (wall->draw_end >= SCREEN_HEIGHT)
		wall->draw_end = SCREEN_HEIGHT - 1;
}

mlx_texture_t	*select_texture(t_data *data, t_ray *ray, int side)
{
	if (side == 0)
	{
		if (ray->dir_x > 0)
			return (data->ea_texture);
		return (data->we_texture);
	}
	if (ray->dir_y > 0)
		return (data->so_texture);
	return (data->no_texture);
}

int	calc_tex_x(t_ray *ray, t_data *data, mlx_texture_t *texture, int side)
{
	double	wall_x;
	int		tex_x;

	if (side == 0)
		wall_x = data->player.player_y / TILE_SIZE + ray->distance * ray->dir_y;
	else
		wall_x = data->player.player_x / TILE_SIZE + ray->distance * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * texture->width);
	if (side == 0 && ray->dir_x > 0)
		tex_x = texture->width - tex_x - 1;
	if (side == 1 && ray->dir_y < 0)
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

void	calc_ray_values(t_ray *ray, t_player *player, double ray_angle)
{
	if (ray->wall_hit == 0)
		ray->distance = (ray->map_x - player->player_x / TILE_SIZE + (1
					- ray->step_x) / 2) / ray->dir_x;
	else
		ray->distance = (ray->map_y - player->player_y / TILE_SIZE + (1
					- ray->step_y) / 2) / ray->dir_y;
	ray->angle = ray_angle;
	ray->hit_x = player->player_x + ray->dir_x * ray->distance;
	ray->hit_y = player->player_y + ray->dir_y * ray->distance;
}
