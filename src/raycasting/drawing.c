/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:42:00 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/05 17:49:40 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void draw_scene_wrapper(void *param)
{
    t_draw_params *params;
	params = (t_draw_params *)param;
    if (!params || !params->data || !params->img)
        return;
    draw_scene(params->data, params->img);
}

static void init_ray(t_data *data, int x, t_ray *ray)
{
    double camera_x;

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

static void calc_step_and_side_dist(t_data *data, t_ray *ray)
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

static int perform_dda(t_data *data, t_ray *ray)
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

static void draw_wall_line(mlx_image_t *img, t_wall *wall, int x)
{
    int y;

    y = wall->draw_start;
    while (y <= wall->draw_end)
    {
        if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
            mlx_put_pixel(img, x, y, wall->color);
        y++;
    }
}

static void calc_wall_props(t_ray *ray, t_wall *wall, int side)
{
    double perp_wall_dist;

    if (side == 0)
        perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
    else
        perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
    wall->height = (int)(SCREEN_HEIGHT / perp_wall_dist);
    wall->draw_start = -wall->height / 2 + SCREEN_HEIGHT / 2;
    if (wall->draw_start < 0)
        wall->draw_start = 0;
    wall->draw_end = wall->height / 2 + SCREEN_HEIGHT / 2;
    if (wall->draw_end >= SCREEN_HEIGHT) 
		wall->draw_end = SCREEN_HEIGHT - 1;
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

void draw_scene(t_data *data, mlx_image_t *img)
{
    t_ray   ray;
    t_wall  wall;
    int     x;
    int     side;

    if (!data || !img || !data->map)
        return ;
    x = 0;
    while (x < SCREEN_WIDTH)
    {
        init_ray(data, x, &ray);
        calc_step_and_side_dist(data, &ray);
        side = perform_dda(data, &ray);
        calc_wall_props(&ray, &wall, side);
        draw_wall_line(img, &wall, x);
        x++;
    }
}
