/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyshandling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:34:40 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/06 22:06:07 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	set_wall_color(t_ray *ray, t_wall *wall, int side)
{
	if (side == 0)
	{
		if (ray->dir_x > 0)
			wall->color = 0xFF0000FF;
		else
			wall->color = 0xCC0000FF;
	}
	else
	{
		if (ray->dir_y > 0)
			wall->color = 0x0000FFFF;
		else
			wall->color = 0x0000CCFF;
	}
}

static void	handle_movement(t_data *data, double new_x, double new_y)
{
	if (data->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] != '1')
	{
		data->player.player_x = new_x;
		data->player.player_y = new_y;
	}
}

static void	handle_wasd(t_data *data)
{
	double	new_x;
	double	new_y;

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		new_x = data->player.player_x + cos(data->player.angle) * PLAYER_SPEED;
		new_y = data->player.player_y - sin(data->player.angle) * PLAYER_SPEED;
		handle_movement(data, new_x, new_y);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		new_x = data->player.player_x - cos(data->player.angle) * PLAYER_SPEED;
		new_y = data->player.player_y + sin(data->player.angle) * PLAYER_SPEED;
		handle_movement(data, new_x, new_y);
	}
}

static void	handle_ad(t_data *data)
{
	double	new_x;
	double	new_y;

	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		new_x = data->player.player_x - sin(data->player.angle) * PLAYER_SPEED;
		new_y = data->player.player_y - cos(data->player.angle) * PLAYER_SPEED;
		handle_movement(data, new_x, new_y);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		new_x = data->player.player_x + sin(data->player.angle) * PLAYER_SPEED;
		new_y = data->player.player_y + cos(data->player.angle) * PLAYER_SPEED;
		handle_movement(data, new_x, new_y);
	}
}

void	handle_keypress(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data || !data->mlx)
		return ;
	handle_wasd(data);
	handle_ad(data);
	handle_rotation(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}
