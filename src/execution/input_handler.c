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

static int check_collision(t_data *data, double new_x, double new_y)
{
    int map_x;
    int map_y;
    int old_map_x;
    int old_map_y;
    
    old_map_x = (int)(data->player.player_x / TILE_SIZE);
    old_map_y = (int)(data->player.player_y / TILE_SIZE);
    map_x = (int)(new_x / TILE_SIZE);
    map_y = (int)(new_y / TILE_SIZE);
    if (map_x != old_map_x && map_y != old_map_y)
    {
        if (data->map[old_map_y][map_x] == '1' || 
            data->map[map_y][old_map_x] == '1')
            return (1);
    }
    if (data->map[map_y][map_x] == '1')
        return (1);
    return (0);
}

static void handle_forward_back(t_data *data, double move_speed)
{
    double  newx;
    double  newy;

    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        newx = data->player.player_x + cos(data->player.angle) * move_speed;
        newy = data->player.player_y + sin(data->player.angle) * move_speed;
        if (!check_collision(data, newx, newy))
        {
            data->player.player_x = newx;
            data->player.player_y = newy;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        newx = data->player.player_x - cos(data->player.angle) * move_speed;
        newy = data->player.player_y - sin(data->player.angle) * move_speed;
        if (!check_collision(data, newx, newy))
        {
            data->player.player_x = newx;
            data->player.player_y = newy;
        }
    }
}

static void handle_strafe(t_data *data, double move_speed)
{
    double  newx;
    double  newy;

    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        newx = data->player.player_x + sin(data->player.angle) * move_speed;
        newy = data->player.player_y - cos(data->player.angle) * move_speed;
        if (!check_collision(data, newx, newy))
        {
            data->player.player_x = newx;
            data->player.player_y = newy;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        newx = data->player.player_x - sin(data->player.angle) * move_speed;
        newy = data->player.player_y + cos(data->player.angle) * move_speed;
        if (!check_collision(data, newx, newy))
        {
            data->player.player_x = newx;
            data->player.player_y = newy;
        }
    }
}

void handle_input(void *param)
{
    t_data  *data;
    static int  cooldown = 0;
    static bool minimap_toggle = true;
    double  move_speed;
    double  rot_speed;

    data = (t_data *)param;
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
