/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:27:27 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/03 23:37:30 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_square(t_data *data, int x, int y, int size, uint32_t color)
{
    int i;
    int j;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            mlx_put_pixel(data->img, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void draw_minimap(t_data *data)
{
    int x;
    int y;
    int square_size = MINIMAP_TILE_SIZE;
    int map_pos_x = 20;
    int map_pos_y = 20;
	
    for (int i = -5; i < data->width * square_size + 5; i++)
        for (int j = -5; j < data->height * square_size + 5; j++)
            mlx_put_pixel(data->img, map_pos_x + i, map_pos_y + j, 0x222222FF);

    y = 0;
    while (y < data->height)
    {
        x = 0;
        while (x < data->width)
        {
            int screen_x = map_pos_x + (x * square_size);
            int screen_y = map_pos_y + (y * square_size);
            
            uint32_t color;
            if (data->map[y][x] == '1')
                color = 0xFFFFFFFF;
            else if (data->map[y][x] == '0')
                color = 0x444444FF;
            else
                color = 0x000000FF;
            draw_square(data, screen_x, screen_y, square_size - 1, color);
            x++;
        }
        y++;
    }
    int player_x = map_pos_x + (int)(data->player.player_x / TILE_SIZE * square_size);
    int player_y = map_pos_y + (int)(data->player.player_y / TILE_SIZE * square_size);
    int line_length = square_size;
    draw_square(data, player_x - 2, player_y - 2, 4, 0xFF0000FF);
    for (int i = 0; i < line_length; i++)
    {
        int x = player_x + (int)(cos(data->player.angle) * i);
        int y = player_y + (int)(sin(data->player.angle) * i);
        mlx_put_pixel(data->img, x, y, 0x00FF00FF);
    }
}


void	handle_input(t_data *data)
{
	double		move_speed;
	double		rot_speed;
	double		newX;
	double		newY;
	static bool	minimap_toggle = true;
    static int	cooldown = 0;
	
    if (!data || !data->mlx)
        return ;
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_M) && cooldown == 0)
    {
        minimap_toggle = !minimap_toggle;
        data->minimap.is_visible = minimap_toggle;
        cooldown = 20;
    }
    if (cooldown > 0)
        cooldown--;
    move_speed = PLAYER_SPEED;
    rot_speed = ROTATION_SPEED;
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        newX = data->player.player_x + cos(data->player.angle) * move_speed;
        newY = data->player.player_y + sin(data->player.angle) * move_speed;
        if (data->map[(int)(newY / TILE_SIZE)][(int)(newX / TILE_SIZE)] != '1')
        {
            data->player.player_x = newX;
            data->player.player_y = newY;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        newX = data->player.player_x - cos(data->player.angle) * move_speed;
        newY = data->player.player_y - sin(data->player.angle) * move_speed;
        if (data->map[(int)(newY / TILE_SIZE)][(int)(newX / TILE_SIZE)] != '1')
        {
            data->player.player_x = newX;
            data->player.player_y = newY;
        }
    }
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
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        newX = data->player.player_x + sin(data->player.angle) * move_speed;
        newY = data->player.player_y - cos(data->player.angle) * move_speed;
        if (data->map[(int)(newY / TILE_SIZE)][(int)(newX / TILE_SIZE)] != '1')
        {
            data->player.player_x = newX;
            data->player.player_y = newY;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        newX = data->player.player_x - sin(data->player.angle) * move_speed;
        newY = data->player.player_y + cos(data->player.angle) * move_speed;
        if (data->map[(int)(newY / TILE_SIZE)][(int)(newX / TILE_SIZE)] != '1')
        {
            data->player.player_x = newX;
            data->player.player_y = newY;
        }
    }
}

void render_walls(t_data *data)
{
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        double ray_dir_x = cos(data->player.angle) - sin(data->player.angle) * camera_x;
        double ray_dir_y = sin(data->player.angle) + cos(data->player.angle) * camera_x;
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        int map_x = (int)(data->player.player_x / TILE_SIZE);
        int map_y = (int)(data->player.player_y / TILE_SIZE);
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
        int side;
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
        if (hit)
        {
            double wall_dist;
            if (side == 0)
                wall_dist = (map_x - data->player.player_x / TILE_SIZE + 
                          (1 - step_x) / 2) / ray_dir_x;
            else
                wall_dist = (map_y - data->player.player_y / TILE_SIZE + 
                          (1 - step_y) / 2) / ray_dir_y;
            int line_height = (int)(SCREEN_HEIGHT / wall_dist);
            int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
            if (draw_start < 0) draw_start = 0;
            int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
            if (draw_end >= SCREEN_HEIGHT) draw_end = SCREEN_HEIGHT - 1;
            uint32_t color = (side == 1) ? 0xFF0000FF : 0xCC0000FF;
            for (int y = draw_start; y < draw_end; y++)
                mlx_put_pixel(data->img, x, y, color);
        }
    }
}

void	game_loop(void *param)
{
    t_data		*data;
	int			x;
	int			y;
	uint32_t	color;
	
	data = (t_data *)param;
    if (!data || !data->mlx || !data->img)
        return;
    handle_input(data);
	y = 0;
    while (y < SCREEN_HEIGHT)
    {
		x = 0;
        while(x < SCREEN_WIDTH)
        {
            color = (y < SCREEN_HEIGHT / 2) ? data->ceiling_color : data->floor_color;
            mlx_put_pixel(data->img, x, y, color);
			x++;
        }
		y++;
    }
    render_walls(data);
	if (data->minimap.is_visible)
		draw_minimap(data);
}

int main(int argc, char **argv)
{
    t_data      data;
    mlx_image_t *img;
    int         fd;

    if (argc != 2 || !check_file_extension(argv[1]))
        return (printf("Error\nInvalid arguments\n"), 1);
    init_data(&data);
    data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
    if (!data.mlx)
        return (printf("Error\nFailed to initialize MLX\n"), 1);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0 || !save_content(get_next_line(fd), &data, fd))
        return (printf("Error\nFailed to parse map\n"), 1);
    init_player(&data);
    img = mlx_new_image(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!img)
        return (printf("Error\nFailed to create MLX image\n"), 1);
    data.img = img;
    if (mlx_image_to_window(data.mlx, img, 0, 0) < 0)
    {
        mlx_delete_image(data.mlx, img);
        return (printf("Error\nFailed to add image to window\n"), 1);
    }
    mlx_loop_hook(data.mlx, game_loop, &data);
    mlx_loop(data.mlx);
    mlx_delete_image(data.mlx, img);
    mlx_terminate(data.mlx);
    return (0);
}
