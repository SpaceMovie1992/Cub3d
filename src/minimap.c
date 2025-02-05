/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:08:38 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/05 20:28:34 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void draw_minimap_background(t_data *data, int map_pos_x, int map_pos_y,
    int square_size)
{
    int i;
    int j;
    int max_width;
    int max_height;

    max_width = data->width * square_size + 5;
    max_height = data->height * square_size + 5;
    i = -5;
    while (i < max_width)
    {
        j = -5;
        while (j < max_height)
        {
            mlx_put_pixel(data->img, map_pos_x + i, map_pos_y + j, 0x222222FF);
            j++;
        }
        i++;
    }
}

static uint32_t get_tile_color(char tile)
{
    if (tile == '1')
        return (0xFFFFFFFF);
    else if (tile == '0')
        return (0x444444FF);
    return (0x000000FF);
}

static void draw_map_tiles(t_data *data, int map_pos_x, int map_pos_y,
    int square_size)
{
    int x;
    int y;
    int screen_x;
    int screen_y;

    y = 0;
    while (y < data->height)
    {
        x = 0;
        while (x < data->width)
        {
            screen_x = map_pos_x + (x * square_size);
            screen_y = map_pos_y + (y * square_size);
            draw_square(data, screen_x, screen_y, square_size - 1,
                get_tile_color(data->map[y][x]));
            x++;
        }
        y++;
    }
}

static void draw_player_direction(t_data *data, int player_x, int player_y,
    int line_length)
{
    int i;
    int x;
    int y;

    i = 0;
    while (i < line_length)
    {
        x = player_x + (int)(cos(data->player.angle) * i);
        y = player_y + (int)(sin(data->player.angle) * i);
        mlx_put_pixel(data->img, x, y, 0x00FF00FF);
        i++;
    }
}

void draw_minimap(t_data *data)
{
    int square_size;
    int map_pos_x;
    int map_pos_y;
    int player_x;
    int player_y;

    square_size = MINIMAP_TILE_SIZE;
    map_pos_x = 20;
    map_pos_y = 20;
    draw_minimap_background(data, map_pos_x, map_pos_y, square_size);
    draw_map_tiles(data, map_pos_x, map_pos_y, square_size);
    player_x = map_pos_x + (int)(data->player.player_x / TILE_SIZE * square_size);
    player_y = map_pos_y + (int)(data->player.player_y / TILE_SIZE * square_size);
    draw_square(data, player_x - 2, player_y - 2, 4, 0xFF0000FF);
    draw_player_direction(data, player_x, player_y, square_size);
}
