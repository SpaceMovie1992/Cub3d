/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:11:55 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/01 20:45:59 by mstefano         ###   ########.fr       */
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
		ray.distance = (map_x - player->player_x
				/ TILE_SIZE + (1 - step_x) / 2) / ray_dir_x;
	else
		ray.distance = (map_y - player->player_y
				/ TILE_SIZE + (1 - step_y) / 2) / ray_dir_y;
	ray.angle = ray_angle;
	ray.hit_x = player->player_x + ray_dir_x * ray.distance;
	ray.hit_y = player->player_y + ray_dir_y * ray.distance;
	return (ray);
}

void draw_scene(t_data *data, mlx_image_t *img)
{
    if (!data || !img)
        return ;
    if (!data->map)
        return ;
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        double ray_dir_x = cos(data->player.angle) - sin(data->player.angle) * camera_x;
        double ray_dir_y = -sin(data->player.angle) - cos(data->player.angle) * camera_x;
        int map_x = (int)(data->player.player_x / TILE_SIZE);
        int map_y = (int)(data->player.player_y / TILE_SIZE);
        double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
        double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
        double side_dist_x;
        double side_dist_y;
        int step_x;
        int step_y;

        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (data->player.player_x / TILE_SIZE - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - data->player.player_x / TILE_SIZE) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (data->player.player_y / TILE_SIZE - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - data->player.player_y / TILE_SIZE) * delta_dist_y;
        }
        int hit = 0;
        int side = 0;
        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }

            if (map_x < 0 || map_y < 0 || map_x >= data->width || map_y >= data->height)
                break;
            if (data->map[map_y][map_x] == '1')
                hit = 1;
        }
        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = side_dist_x - delta_dist_x;
        else
            perp_wall_dist = side_dist_y - delta_dist_y;
        int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
        int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_end >= SCREEN_HEIGHT)
            draw_end = SCREEN_HEIGHT - 1;
        uint32_t color;
        if (side == 0)
            color = (ray_dir_x > 0) ? 0xFF0000FF : 0xCC0000FF;
        else
            color = (ray_dir_y > 0) ? 0x0000FFFF : 0x0000CCFF;
        for (int y = draw_start; y <= draw_end; y++)
        {
            if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
                mlx_put_pixel(img, x, y, color);
        }
    }
}

void draw_scene_wrapper(void *param)
{
    t_draw_params *params = (t_draw_params *)param;
    if (!params || !params->data || !params->img)
        return;
    draw_scene(params->data, params->img);
}

void key_hook(void *param)
{
    t_data *data;

    data = (t_data *)param;
    if (!data || !data->mlx || !data->map)
    	return ;
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        double new_x = data->player.player_x + cos(data->player.angle) * PLAYER_SPEED;
        double new_y = data->player.player_y - sin(data->player.angle) * PLAYER_SPEED;
        int map_x = (int)(new_x / TILE_SIZE);
        int map_y = (int)(new_y / TILE_SIZE);
        
        if (map_x >= 0 && map_x < data->width && map_y >= 0 && map_y < data->height)
        {
            if (data->map[map_y][map_x] != '1')
            {
                data->player.player_x = new_x;
                data->player.player_y = new_y;
            }
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        int new_x = (int)((data->player.player_x - cos(data->player.angle) * PLAYER_SPEED) / TILE_SIZE);
        int new_y = (int)((data->player.player_y + sin(data->player.angle) * PLAYER_SPEED) / TILE_SIZE);
        
        if (new_x >= 0 && new_x < data->width && new_y >= 0 && new_y < data->height)
        {
            if (data->map[new_y][new_x] != '1')
            {
                data->player.player_x -= cos(data->player.angle) * PLAYER_SPEED;
                data->player.player_y += sin(data->player.angle) * PLAYER_SPEED;
            }
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        int new_x = (int)((data->player.player_x - sin(data->player.angle) * PLAYER_SPEED) / TILE_SIZE);
        int new_y = (int)((data->player.player_y - cos(data->player.angle) * PLAYER_SPEED) / TILE_SIZE);
        
        if (new_x >= 0 && new_x < data->width && new_y >= 0 && new_y < data->height)
        {
            if (data->map[new_y][new_x] != '1')
            {
                data->player.player_x -= sin(data->player.angle) * PLAYER_SPEED;
                data->player.player_y -= cos(data->player.angle) * PLAYER_SPEED;
            }
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        int new_x = (int)((data->player.player_x + sin(data->player.angle) * PLAYER_SPEED) / TILE_SIZE);
        int new_y = (int)((data->player.player_y + cos(data->player.angle) * PLAYER_SPEED) / TILE_SIZE);   
        if (new_x >= 0 && new_x < data->width && new_y >= 0 && new_y < data->height)
        {
            if (data->map[new_y][new_x] != '1')
            {
                data->player.player_x += sin(data->player.angle) * PLAYER_SPEED;
                data->player.player_y += cos(data->player.angle) * PLAYER_SPEED;
            }
        }
    }
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
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
}

void init_player(t_data *data)
{
    if (!data || !data->map)
        return ;
    data->player.player_x = (double)(data->pos_x * TILE_SIZE) + (TILE_SIZE / 2.0);
    data->player.player_y = (double)(data->pos_y * TILE_SIZE) + (TILE_SIZE / 2.0);
    if (data->player_dir == 'N')
        data->player.angle = 3.0 * M_PI / 2.0;
    else if (data->player_dir == 'S')
        data->player.angle = M_PI / 2.0;
    else if (data->player_dir == 'E')
        data->player.angle = 0.0;
    else if (data->player_dir == 'W')
        data->player.angle = M_PI;
    data->player.fov = FOV;
    data->player.rotation = 0;
    data->player.l_r = 0;
    data->player.u_d = 0;
}

void handle_keypress(void *param)
{
    t_data *data = (t_data *)param;
    
    if (!data || !data->mlx)
        return ;
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        double new_x = data->player.player_x + cos(data->player.angle) * PLAYER_SPEED;
        double new_y = data->player.player_y - sin(data->player.angle) * PLAYER_SPEED;  // Note the minus sign
        if (data->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] != '1')
        {
            data->player.player_x = new_x;
            data->player.player_y = new_y;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        double new_x = data->player.player_x - cos(data->player.angle) * PLAYER_SPEED;
        double new_y = data->player.player_y + sin(data->player.angle) * PLAYER_SPEED;  // Note the plus sign
        if (data->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] != '1')
        {
            data->player.player_x = new_x;
            data->player.player_y = new_y;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        double new_x = data->player.player_x - sin(data->player.angle) * PLAYER_SPEED;
        double new_y = data->player.player_y - cos(data->player.angle) * PLAYER_SPEED;
        if (data->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] != '1')
        {
            data->player.player_x = new_x;
            data->player.player_y = new_y;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        double new_x = data->player.player_x + sin(data->player.angle) * PLAYER_SPEED;
        double new_y = data->player.player_y + cos(data->player.angle) * PLAYER_SPEED;
        if (data->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] != '1')
        {
            data->player.player_x = new_x;
            data->player.player_y = new_y;
        }
    }
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
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
}

void render_frame(void *param)
{
    t_draw_params *params = (t_draw_params *)param;
    if (!params || !params->data || !params->img)
        return;
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            if (y < SCREEN_HEIGHT / 2)
                mlx_put_pixel(params->img, x, y, params->data->ceiling_color);
            else
                mlx_put_pixel(params->img, x, y, params->data->floor_color);
        }
    }
    draw_scene(params->data, params->img);
}
