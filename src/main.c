/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:27:27 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/04 17:28:42 by mstefano         ###   ########.fr       */
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

static mlx_texture_t *scale_texture(mlx_texture_t *texture, int new_width, int new_height)
{
    mlx_texture_t *scaled;

    scaled = malloc(sizeof(mlx_texture_t));
    if (!scaled)
        return (NULL);
    scaled->width = new_width;
    scaled->height = new_height;
    scaled->pixels = malloc(new_width * new_height * 4);
    if (!scaled->pixels)
    {
        free(scaled);
        return (NULL);
    }
    // Simple scaling
    for (int y = 0; y < new_height; y++)
    {
        for (int x = 0; x < new_width; x++)
        {
            int src_x = x * texture->width / new_width;
            int src_y = y * texture->height / new_height;
            int src_index = (src_y * texture->width + src_x) * 4;
            int dst_index = (y * new_width + x) * 4;
            
            scaled->pixels[dst_index] = texture->pixels[src_index];
            scaled->pixels[dst_index + 1] = texture->pixels[src_index + 1];
            scaled->pixels[dst_index + 2] = texture->pixels[src_index + 2];
            scaled->pixels[dst_index + 3] = texture->pixels[src_index + 3];
        }
    }
    return (scaled);
}

bool load_textures(t_data *data)
{
	mlx_texture_t *temp_we;
	
    if (!data->no_texture_path || !data->so_texture_path || 
        !data->we_texture_path || !data->ea_texture_path)
        return (false);
    mlx_texture_t *temp_no = mlx_load_png(data->no_texture_path);
    if (!temp_no)
        return (false);
    data->no_texture = scale_texture(temp_no, TEXTURE_SIZE, TEXTURE_SIZE);
    mlx_delete_texture(temp_no);
    if (!data->no_texture)
        return (false);
    data->so_texture = data->no_texture;
    temp_we = mlx_load_png(data->we_texture_path);
    if (!temp_we)
        return (mlx_delete_texture(data-> no_texture), false);
    data->we_texture = scale_texture(temp_we, TEXTURE_SIZE, TEXTURE_SIZE);
    mlx_delete_texture(temp_we);
    if (!data->we_texture)
        return (mlx_delete_texture(data->no_texture), false);
    data->ea_texture = data->we_texture;
    return (true);
}

void cleanup_textures(t_data *data)
{
    if (data->no_texture)
        mlx_delete_texture(data->no_texture);
    if (data->we_texture)
        mlx_delete_texture(data->we_texture);
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
            if (draw_start < 0) 
                draw_start = 0;
            int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
            if (draw_end >= SCREEN_HEIGHT) 
                draw_end = SCREEN_HEIGHT - 1;

            // Select texture based on wall orientation
            mlx_texture_t *texture;
            if (side == 0)
                texture = (ray_dir_x > 0) ? data->ea_texture : data->we_texture;
            else
                texture = (ray_dir_y > 0) ? data->so_texture : data->no_texture;

            // Calculate wall X coordinate
            double wall_x;
            if (side == 0)
                wall_x = data->player.player_y / TILE_SIZE + wall_dist * ray_dir_y;
            else
                wall_x = data->player.player_x / TILE_SIZE + wall_dist * ray_dir_x;
            wall_x -= floor(wall_x);

            // Calculate texture coordinates
            int tex_x = (int)(wall_x * texture->width);
            if (side == 0 && ray_dir_x > 0)
                tex_x = texture->width - tex_x - 1;
            if (side == 1 && ray_dir_y < 0)
                tex_x = texture->width - tex_x - 1;

            // Draw the textured wall column
            double step = 1.0 * texture->height / line_height;
            double tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;

            for (int y = draw_start; y < draw_end; y++)
            {
                int tex_y = (int)tex_pos & (texture->height - 1);
                tex_pos += step;

                uint8_t *pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
                
                // Add distance shading
                double shade = 1.0 / (1.0 + wall_dist * wall_dist * 0.0001);
                shade = fmin(1.0, fmax(0.3, shade));

                uint32_t color = ((uint32_t)(pixel[0] * shade) << 24) |
                                ((uint32_t)(pixel[1] * shade) << 16) |
                                ((uint32_t)(pixel[2] * shade) << 8) |
                                pixel[3];

                mlx_put_pixel(data->img, x, y, color);
            }
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
    
    printf("Opening map file: %s\n", argv[1]);
    
    init_data(&data);
    data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
    if (!data.mlx)
        return (printf("Error\nFailed to initialize MLX\n"), 1);

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (printf("Error\nCannot open map file\n"), 1);

    if (!save_content(get_next_line(fd), &data, fd))
    {
        close(fd);
        mlx_terminate(data.mlx);
        return (printf("Error\nFailed during map parsing\n"), 1);
    }
    close(fd);

    if (!load_textures(&data))
    {
        mlx_terminate(data.mlx);
        return (printf("Error\nFailed to load textures\n"), 1);
    }

    init_player(&data);
    img = mlx_new_image(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!img)
    {
        cleanup_textures(&data);
        mlx_terminate(data.mlx);
        return (printf("Error\nFailed to create MLX image\n"), 1);
    }
    data.img = img;

    if (mlx_image_to_window(data.mlx, img, 0, 0) < 0)
    {
        cleanup_textures(&data);
        mlx_delete_image(data.mlx, img);
        mlx_terminate(data.mlx);
        return (printf("Error\nFailed to add image to window\n"), 1);
    }

    mlx_loop_hook(data.mlx, game_loop, &data);
    mlx_loop(data.mlx);

    cleanup_textures(&data);
    mlx_delete_image(data.mlx, img);
    mlx_terminate(data.mlx);
    return (0);
}
