/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:27:27 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/05 20:27:12 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
    if (fd < 0)
        return (printf("Error\nCannot open map file\n"), 1);
    if (!save_content(get_next_line(fd), &data, fd))
    {
        close(fd);
        mlx_terminate(data.mlx);
    }
    close(fd);
    if (!load_textures(&data))
        mlx_terminate(data.mlx);
    init_player(&data);
    img = mlx_new_image(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!img)
    {
        cleanup_textures(&data);
        mlx_terminate(data.mlx);
    }
    data.img = img;
    if (mlx_image_to_window(data.mlx, img, 0, 0) < 0)
    {
        cleanup_textures(&data);
        mlx_delete_image(data.mlx, img);
        mlx_terminate(data.mlx);
    }
    mlx_loop_hook(data.mlx, game_loop, &data);
    mlx_loop(data.mlx);
    cleanup_textures(&data);
    mlx_delete_image(data.mlx, img);
    mlx_terminate(data.mlx);
    return (0);
}
