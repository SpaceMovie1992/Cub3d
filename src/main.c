/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:27:27 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/03 22:22:01 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	handle_input(t_data *data)
{
	double move_speed;
	double rot_speed;
	double newX;
	double newY;

    if (!data || !data->mlx)
        return ;
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
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
        double side_dist_x, side_dist_y;
        int step_x, step_y, hit = 0, side;

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
        while (!hit)
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
            if (data->map[map_y][map_x] == '1')
                hit = 1;
        }
        double wall_dist = (side == 0)
            ? (map_x - data->player.player_x / TILE_SIZE + (1 - step_x) / 2) / ray_dir_x
            : (map_y - data->player.player_y / TILE_SIZE + (1 - step_y) / 2) / ray_dir_y;
        int line_height = (int)(SCREEN_HEIGHT / wall_dist);
        int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
        int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;

        double wall_x = (side == 0) ? (data->player.player_y + wall_dist * ray_dir_y)
                                    : (data->player.player_x + wall_dist * ray_dir_x);
        wall_x -= floor(wall_x);

		t_texture *texture;
		if (side == 0)
    		texture = *((ray_dir_x > 0) ? &data->ea_texture : &data->we_texture);
		else
    		texture = *((ray_dir_y > 0) ? &data->so_texture : &data->no_texture);

        int tex_x = (int)(wall_x * (double)(texture->width));

        for (int y = draw_start; y < draw_end; y++)
        {
            int tex_y = ((y - draw_start) * texture->height) / line_height;
            uint32_t color = get_texture_pixel(texture, tex_x, tex_y);
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
}

int main(int argc, char **argv)
{
    t_data      data;
    mlx_image_t *img;
    int         fd;

	// Debugging: Check arguments
    printf("Arguments count: %d\n", argc);
    if (argc != 2 || !check_file_extension(argv[1]))
    {
        printf("Error: Invalid arguments or file extension\n");
        return (1);
    }

    if (argc != 2 || !check_file_extension(argv[1]))
        return (printf("Error\nInvalid arguments\n"), 1);
	printf("Initializing data\n");
    init_data(&data);
    data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
    if (!data.mlx)
        return (printf("Error\nFailed to initialize MLX\n"), 1);
    printf("Opening file: %s\n", argv[1]);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0 || !save_content(get_next_line(fd), &data, fd))
	{
		cleanup_all_textures(&data);
		if(!data.map)
			mlx_terminate(data.mlx);
    	return (printf("Failed to parse map\n"), 1);
	}
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
