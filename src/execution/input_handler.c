/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:17:44 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/10 22:19:22 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	handle_minimap(t_data *data, int *cooldown, bool *minimap_toggle)
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

static void	handle_rotate(t_data *data, double rot_speed)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.angle -= rot_speed;
		if (data->player.angle < 0)
			data->player.angle += 2 * M_PI;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.angle += rot_speed;
		if (data->player.angle >= 2 * M_PI)
			data->player.angle -= 2 * M_PI;
	}
}

static void	handle_forward_back(t_data *data, double move_speed)
{
	double	newx;
	double	newy;

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		newx = data->player.player_x + cos(data->player.angle) * move_speed;
		newy = data->player.player_y + sin(data->player.angle) * move_speed;
		if (data->map[(int)(newy / TILE_SIZE)][(int)(newx / TILE_SIZE)] != '1')
		{
			data->player.player_x = newx;
			data->player.player_y = newy;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		newx = data->player.player_x - cos(data->player.angle) * move_speed;
		newy = data->player.player_y - sin(data->player.angle) * move_speed;
		if (data->map[(int)(newy / TILE_SIZE)][(int)(newx / TILE_SIZE)] != '1')
		{
			data->player.player_x = newx;
			data->player.player_y = newy;
		}
	}
}

static void	handle_strafe(t_data *data, double move_speed)
{
	double	newx;
	double	newy;

	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		newx = data->player.player_x + sin(data->player.angle) * move_speed;
		newy = data->player.player_y - cos(data->player.angle) * move_speed;
		if (data->map[(int)(newy / TILE_SIZE)][(int)(newx / TILE_SIZE)] != '1')
		{
			data->player.player_x = newx;
			data->player.player_y = newy;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		newx = data->player.player_x - sin(data->player.angle) * move_speed;
		newy = data->player.player_y + cos(data->player.angle) * move_speed;
		if (data->map[(int)(newy / TILE_SIZE)][(int)(newx / TILE_SIZE)] != '1')
		{
			data->player.player_x = newx;
			data->player.player_y = newy;
		}
	}
}

void	handle_input(t_data *data)
{
	static bool	minimap_toggle = false;
	static int	cooldown = 0;
	double		move_speed;
	double		rot_speed;

	if (!data || !data->mlx)
		return ;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	move_speed = PLAYER_SPEED;
	rot_speed = ROTATION_SPEED;
	handle_minimap(data, &cooldown, &minimap_toggle);
	handle_rotate(data, rot_speed);
	handle_forward_back(data, move_speed);
	handle_strafe(data, move_speed);
}
