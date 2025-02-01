/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:27:27 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/01 18:11:08 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data || !data->mlx || !data->img)
		return ;
	key_hook(data);
	draw_scene_wrapper(data);
}

int main(int argc, char **argv)
{
    t_data          data;
    mlx_image_t     *img;
    t_draw_params   params;
    int             fd;

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
    params.data = &data;
    params.img = img;
    mlx_key_hook(data.mlx, (mlx_keyfunc)handle_keypress, &data);
    mlx_loop_hook(data.mlx, (void *)render_frame, &params);
    mlx_loop(data.mlx);
    mlx_delete_image(data.mlx, img);
    mlx_terminate(data.mlx);
    return (0);
}
