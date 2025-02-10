/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:27:27 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/10 17:53:13 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

mlx_texture_t	*scale_texture(mlx_texture_t *texture, int new_width,
		int new_height)
{
	mlx_texture_t	*scaled;

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
	scale_pixels(scaled, texture, new_width, new_height);
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

static int	setup_window(t_data *data)
{
	mlx_image_t	*img;

	img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!img)
	{
		cleanup_textures(data);
		mlx_terminate(data->mlx);
		return (0);
	}
	data->img = img;
	if (mlx_image_to_window(data->mlx, img, 0, 0) < 0)
	{
		cleanup_textures(data);
		mlx_delete_image(data->mlx, img);
		mlx_terminate(data->mlx);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2 || !check_file_extension(argv[1]))
		return (printf("Error\nInvalid arguments\n"), 1);
	if (!init_game(&data, argv[1]))
		return (1);
	if (!setup_window(&data))
		return (1);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	cleanup_textures(&data);
	mlx_delete_image(data.mlx, data.img);
	mlx_terminate(data.mlx);
	return (0);
}
