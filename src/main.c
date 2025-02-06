/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:27:27 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/06 18:01:18 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

mlx_texture_t	*scale_texture(mlx_texture_t *texture, int new_width,
		int new_height)
{
	mlx_texture_t	*scaled;
	int				src_x;
	int				src_y;
	int				src_index;
	int				dst_index;

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
			src_x = x * texture->width / new_width;
			src_y = y * texture->height / new_height;
			src_index = (src_y * texture->width + src_x) * 4;
			dst_index = (y * new_width + x) * 4;
			scaled->pixels[dst_index] = texture->pixels[src_index];
			scaled->pixels[dst_index + 1] = texture->pixels[src_index + 1];
			scaled->pixels[dst_index + 2] = texture->pixels[src_index + 2];
			scaled->pixels[dst_index + 3] = texture->pixels[src_index + 3];
		}
	}
	return (scaled);
}

void	game_loop(void *param)
{
	t_data		*data;
	int			x;
	int			y;
	uint32_t	color;

	data = (t_data *)param;
	if (!data || !data->mlx || !data->img)
		return ;
	handle_input(data);
	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			if (y < SCREEN_HEIGHT / 2)
				color = data->cc;
			else
				color = data->fc;
			mlx_put_pixel(data->img, x, y, color);
		}
	}
	render_walls(data);
	if (data->minimap.is_visible)
		draw_minimap(data);
}

int	main(int argc, char **argv)
{
	t_data		data;
	mlx_image_t	*img;
	int			fd;

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
