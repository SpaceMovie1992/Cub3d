/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:11:55 by mstefano          #+#    #+#             */
/*   Updated: 2025/01/30 21:07:46 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_ray	cast_ray(t_data *data, t_player *player, double ray_angle)
{
	t_ray	ray;
	double	ray_dir_x = 0.0;
	double	ray_dir_y = 0.0;
	double	side_dist_x = 0.0;
	double	side_dist_y = 0.0;
	double	delta_dist_x = 0.0;
	double	delta_dist_y = 0.0;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;

	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	map_x = player->player_x / TILE_SIZE;
	map_y = player->player_y / TILE_SIZE;
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	hit = 0;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (player->player_x - map_x * TILE_SIZE) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = ((map_x + 1) * TILE_SIZE - player->player_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (player->player_y - map_y * TILE_SIZE) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = ((map_y + 1) * TILE_SIZE - player->player_y) * delta_dist_y;
	}
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			ray.wall_hit = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			ray.wall_hit = 1;
		}
		if (data->map[map_y][map_x] == '1')
			hit = 1;
	}
	if (ray.wall_hit == 0)
		ray.distance = (map_x - player->player_x / TILE_SIZE + (1 - step_x) / 2) / ray_dir_x;
	else
		ray.distance = (map_y - player->player_y / TILE_SIZE + (1 - step_y) / 2) / ray_dir_y;
	ray.angle = ray_angle;
	ray.hit_x = player->player_x + ray_dir_x * ray.distance;
	ray.hit_y = player->player_y + ray_dir_y * ray.distance;
	return (ray);
}

void	draw_scene(t_data *data, t_player *player, mlx_image_t *img)
{
	int		x;
	int		y;
	double	ray_angle;
	t_ray	ray;
	int		line_height;
	int		draw_start;
	int		draw_end;

	x = 0;
	ray_angle = player->angle + atan((x - SCREEN_WIDTH / 2) / (SCREEN_WIDTH / 2 * tan(player->fov / 2)));
	ray = cast_ray(data, player, ray_angle);
	line_height = (int)(SCREEN_HEIGHT / ray.distance);
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = draw_start;
		while (y < draw_end)
		{
			mlx_put_pixel(img, x, y, 0xFFFFFFFF);
			y++;
		}
		x++;
	}
}

void	key_hook(void *param)
{
	t_data		*data;
	t_player	*player;

	data = NULL;
	player = &data->player;
	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		player->player_x += cos(player->angle) * PLAYER_SPEED;
		player->player_y += sin(player->angle) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		player->player_x -= cos(player->angle) * PLAYER_SPEED;
		player->player_y -= sin(player->angle) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		player->angle -= ROTATION_SPEED;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		player->angle += ROTATION_SPEED;
}

void	init_player(t_data *data)
{
	data->player.player_x = data->pos_x * TILE_SIZE + TILE_SIZE / 2;
	data->player.player_y = data->pos_y * TILE_SIZE + TILE_SIZE / 2;
	if (data->player_dir == 'N')
		data->player.angle = NORTH;
	else if (data->player_dir == 'S')
		data->player.angle = SOUTH;
	else if (data->player_dir == 'W')
		data->player.angle = WEST;
	else if (data->player_dir == 'E')
		data->player.angle = EAST;
	data->player.fov = FOV * (M_PI / 180);
}
