/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallrender.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:46:43 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/05 18:47:37 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void init_ray_values(t_ray *ray, t_data *data, int x)
{
    double camera_x;

    camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
    ray->dir_x = cos(data->player.angle) - sin(data->player.angle) * camera_x;
    ray->dir_y = sin(data->player.angle) + cos(data->player.angle) * camera_x;
    ray->delta_dist_x = fabs(1 / ray->dir_x);
    ray->delta_dist_y = fabs(1 / ray->dir_y);
    ray->map_x = (int)(data->player.player_x / TILE_SIZE);
    ray->map_y = (int)(data->player.player_y / TILE_SIZE);
}

static void calc_step_and_side_dist(t_ray *ray, t_data *data)
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
        ray->side_dist_x = (ray->map_x + 1.0 - data->player.player_x / TILE_SIZE)
            * ray->delta_dist_x;
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
        ray->side_dist_y = (ray->map_y + 1.0 - data->player.player_y / TILE_SIZE)
            * ray->delta_dist_y;
    }
}

static int perform_dda(t_ray *ray, t_data *data)
{
    int hit;
    int side;

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

static void calc_wall_height(t_wall *wall, t_ray *ray, t_data *data, int side)
{
    if (side == 0)
        ray->distance = (ray->map_x - data->player.player_x / TILE_SIZE
            + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        ray->distance = (ray->map_y - data->player.player_y / TILE_SIZE
            + (1 - ray->step_y) / 2) / ray->dir_y;
    wall->height = (int)(SCREEN_HEIGHT / ray->distance);
    wall->draw_start = -wall->height / 2 + SCREEN_HEIGHT / 2;
    wall->draw_start = (wall->draw_start < 0) ? 0 : wall->draw_start;
    wall->draw_end = wall->height / 2 + SCREEN_HEIGHT / 2;
    wall->draw_end = (wall->draw_end >= SCREEN_HEIGHT) ? 
        SCREEN_HEIGHT - 1 : wall->draw_end;
}

static mlx_texture_t *select_texture(t_data *data, t_ray *ray, int side)
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

static int calc_tex_x(t_ray *ray, t_data *data, mlx_texture_t *texture, int side)
{
    double wall_x;
    int tex_x;

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

static void draw_textured_line(t_data *data, t_wall *wall, t_ray *ray, int x)
{
    int             y;
    double          tex_pos;
    double          step;
    uint8_t         *pixel;
    uint32_t        color;
    double          shade;
    mlx_texture_t   *texture;
    int             tex_x;
    int             tex_y;

    texture = select_texture(data, ray, ray->wall_hit);
    tex_x = calc_tex_x(ray, data, texture, ray->wall_hit);
    step = 1.0 * texture->height / wall->height;
    tex_pos = (wall->draw_start - SCREEN_HEIGHT / 2 + wall->height / 2) * step;
    y = wall->draw_start;
    while (y < wall->draw_end)
    {
        tex_y = (int)tex_pos & (texture->height - 1);
        tex_pos += step;
        pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
        shade = 1.0 / (1.0 + ray->distance * ray->distance * 0.0001);
        shade = fmin(1.0, fmax(0.3, shade));
        color = ((uint32_t)(pixel[0] * shade) << 24)
            | ((uint32_t)(pixel[1] * shade) << 16)
            | ((uint32_t)(pixel[2] * shade) << 8) | pixel[3];
        mlx_put_pixel(data->img, x, y, color);
        y++;
    }
}

void render_walls(t_data *data)
{
    t_ray   ray;
    t_wall  wall;
    int     x;
    int     side;

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
