/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:27:27 by mstefano          #+#    #+#             */
/*   Updated: 2025/01/30 21:08:18 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_data		data;
	mlx_image_t	*img;
	int			fd;

	if (argc != 2 || !check_file_extension(argv[1]))
		return (printf("Error\nInvalid arguments\n"), 1);
	data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (!data.mlx)
		return (printf("Error\nFailed to initialize MLX\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || !save_content(get_next_line(fd), &data, fd))
		return (printf("Error\nFailed to parse map\n"), 1);
	init_player(&data);
	img = mlx_new_image(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(data.mlx, img, 0, 0);
	mlx_loop_hook(data.mlx, key_hook, &data);
	mlx_loop_hook(data.mlx, (void *)draw_scene, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
