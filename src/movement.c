/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:10:56 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/05 20:30:56 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void move_forward(t_data *data)
{
    double new_x;
    double new_y;
    int    map_x;
    int    map_y;

    new_x = data->player.player_x + cos(data->player.angle) * PLAYER_SPEED;
    new_y = data->player.player_y - sin(data->player.angle) * PLAYER_SPEED;
    map_x = (int)(new_x / TILE_SIZE);
    map_y = (int)(new_y / TILE_SIZE);
    if (is_valid_pos(data, map_x, map_y))
    {
        data->player.player_x = new_x;
        data->player.player_y = new_y;
    }
}

static void move_backward(t_data *data)
{
    int new_x;
    int new_y;

    new_x = (int)((data->player.player_x - cos(data->player.angle)
            * PLAYER_SPEED) / TILE_SIZE);
    new_y = (int)((data->player.player_y + sin(data->player.angle)
            * PLAYER_SPEED) / TILE_SIZE);
    if (is_valid_pos(data, new_x, new_y))
    {
        data->player.player_x -= cos(data->player.angle) * PLAYER_SPEED;
        data->player.player_y += sin(data->player.angle) * PLAYER_SPEED;
    }
}

static void move_left(t_data *data)
{
    int new_x;
    int new_y;

    new_x = (int)((data->player.player_x - sin(data->player.angle)
            * PLAYER_SPEED) / TILE_SIZE);
    new_y = (int)((data->player.player_y - cos(data->player.angle)
            * PLAYER_SPEED) / TILE_SIZE);
    if (is_valid_pos(data, new_x, new_y))
    {
        data->player.player_x -= sin(data->player.angle) * PLAYER_SPEED;
        data->player.player_y -= cos(data->player.angle) * PLAYER_SPEED;
    }
}

static void move_right(t_data *data)
{
    int new_x;
    int new_y;

    new_x = (int)((data->player.player_x + sin(data->player.angle)
            * PLAYER_SPEED) / TILE_SIZE);
    new_y = (int)((data->player.player_y + cos(data->player.angle)
            * PLAYER_SPEED) / TILE_SIZE);
    if (is_valid_pos(data, new_x, new_y))
    {
        data->player.player_x += sin(data->player.angle) * PLAYER_SPEED;
        data->player.player_y += cos(data->player.angle) * PLAYER_SPEED;
    }
}

static void handle_rotation(t_data *data)
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

void key_hook(void *param)
{
    t_data *data;

    data = (t_data *)param;
    if (!data || !data->mlx || !data->map)
        return ;
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
        move_forward(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
        move_backward(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
        move_left(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
        move_right(data);
    handle_rotation(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
}
