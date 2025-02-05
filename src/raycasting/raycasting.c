/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:11:55 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/04 16:11:27 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void init_ray_values(t_ray *ray, t_player *player, double ray_angle)
{
    ray->dir_x = cos(ray_angle);
    ray->dir_y = sin(ray_angle);
    ray->delta_dist_x = fabs(1 / ray->dir_x);
    ray->delta_dist_y = fabs(1 / ray->dir_y);
    ray->map_x = player->player_x / TILE_SIZE;
    ray->map_y = player->player_y / TILE_SIZE;
    ray->wall_hit = 0;
}

static void calc_step_x(t_ray *ray, t_player *player)
{
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (player->player_x - ray->map_x * TILE_SIZE)
            * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = ((ray->map_x + 1) * TILE_SIZE - player->player_x)
            * ray->delta_dist_x;
    }
}

static void calc_step_y(t_ray *ray, t_player *player)
{
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (player->player_y - ray->map_y * TILE_SIZE)
            * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = ((ray->map_y + 1) * TILE_SIZE - player->player_y)
            * ray->delta_dist_y;
    }
}

static void perform_dda(t_ray *ray, t_data *data)
{
    int hit;

    hit = 0;
    while (!hit)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->wall_hit = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->wall_hit = 1;
        }
        if (data->map[ray->map_y][ray->map_x] == '1')
            hit = 1;
    }
}

static void calc_ray_values(t_ray *ray, t_player *player, double ray_angle)
{
    if (ray->wall_hit == 0)
        ray->distance = (ray->map_x - player->player_x / TILE_SIZE
            + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        ray->distance = (ray->map_y - player->player_y / TILE_SIZE
            + (1 - ray->step_y) / 2) / ray->dir_y;
    ray->angle = ray_angle;
    ray->hit_x = player->player_x + ray->dir_x * ray->distance;
    ray->hit_y = player->player_y + ray->dir_y * ray->distance;
}

t_ray cast_ray(t_data *data, t_player *player, double ray_angle)
{
    t_ray ray;

    init_ray_values(&ray, player, ray_angle);
    calc_step_x(&ray, player);
    calc_step_y(&ray, player);
    perform_dda(&ray, data);
    calc_ray_values(&ray, player, ray_angle);
    return (ray);
}

void render_frame(void *param)
{
    t_draw_params	*params;
	int				x;
	int				y;
	params = (t_draw_params *)param;
    if (!params || !params->data || !params->img)
        return ;
	y = 0;
    while (y < SCREEN_HEIGHT)
    {
		x = 0;
        while (x < SCREEN_WIDTH)
        {
            if (y < SCREEN_HEIGHT / 2)
                mlx_put_pixel(params->img, x, y, params->data->ceiling_color);
            else
                mlx_put_pixel(params->img, x, y, params->data->floor_color);
			x++;
        }
		y++;
    }
    draw_scene(params->data, params->img);
}
