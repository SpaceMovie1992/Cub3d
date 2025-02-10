/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:54:49 by mstefano          #+#    #+#             */
/*   Updated: 2025/02/10 21:56:06 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_player(t_data *data)
{
	if (!data || !data->map)
		return ;
	data->player.player_x = (double)(data->pos_x * TILE_SIZE) + (TILE_SIZE
			/ 2.0);
	data->player.player_y = (double)(data->pos_y * TILE_SIZE) + (TILE_SIZE
			/ 2.0);
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

static void	init_data1(t_data *data)
{
	data->width = 0;
	data->fc = 0;
	data->cc = 0;
	data->pos_x = -1;
	data->pos_y = -1;
	data->dir_x = 0;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = 0;
	data->player.player_x = 0;
	data->player.player_y = 0;
	data->player.angle = 0;
	data->player.fov = FOV;
	data->player.rotation = 0;
	data->player.l_r = 0;
	data->player.u_d = 0;
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->img = NULL;
	data->map = NULL;
	data->no_texture = NULL;
	data->so_texture = NULL;
	data->we_texture = NULL;
	data->ea_texture = NULL;
	data->no_texture_path = NULL;
	data->so_texture_path = NULL;
	data->we_texture_path = NULL;
	data->ea_texture_path = NULL;
	data->path = NULL;
	data->player_dir = '\0';
	data->fd = -1;
	data->height = 0;
	init_data1(data);
}

int	init_game(t_data *data, char *map_path)
{
	int	fd;

	init_data(data);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCannot open map file\n"), 0);
	if (!save_content(get_next_line(fd), data, fd))
	{
		close(fd);
		cleanup_texture_paths(data);
		cleanup_map(data);
		return (0);
	}
	close(fd);
	if (!char_position_check(data))
	{
		cleanup_texture_paths(data);
		cleanup_map(data);
		return (0);
	}
	data->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (!data->mlx)
	{
		cleanup_texture_paths(data);
		cleanup_map(data);
		return (printf("Error\nFailed to initialize MLX\n"), 0);
	}
	if (!load_textures(data))
	{
		cleanup_texture_paths(data);
		cleanup_map(data);
		mlx_terminate(data->mlx);
		return (0);
	}
	init_player(data);
	return (1);
}
