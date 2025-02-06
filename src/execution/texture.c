/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:46:44 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/06 19:05:14 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static mlx_texture_t	*select_wall_texture(t_data *data, t_ray *ray)
{
	if (ray->wall_hit == 0)
	{
		if (ray->step_x > 0)
			return (data->ea_texture);
		return (data->we_texture);
	}
	if (ray->step_y > 0)
		return (data->so_texture);
	return (data->no_texture);
}

static double	get_wall_x(t_data *data, t_ray *ray)
{
	double	wall_x;

	if (ray->wall_hit == 0)
		wall_x = data->player.player_y / TILE_SIZE + ray->distance * ray->dir_y;
	else
		wall_x = data->player.player_x / TILE_SIZE + ray->distance * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

static int	get_tex_x(t_ray *ray, double wall_x, mlx_texture_t *texture)
{
	int	tex_x;

	tex_x = (int)(wall_x * texture->width);
	if ((ray->wall_hit == 0 && ray->step_x > 0)
		|| (ray->wall_hit == 1 && ray->step_y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

static void	draw_vertical_line(t_data *data, t_wall *wall,
		mlx_texture_t *texture, int tex_x)
{
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;
	uint8_t	*pixel;

	step = (double)texture->height / wall->height;
	tex_pos = (wall->draw_start - SCREEN_HEIGHT / 2
			+ wall->height / 2) * step;
	y = wall->draw_start;
	while (y < wall->draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
		wall->color = (pixel[0] << 24 | pixel[1] << 16
				| pixel[2] << 8 | pixel[3]);
		mlx_put_pixel(data->img, wall->x, y, wall->color);
		tex_pos += step;
		y++;
	}
}

void	draw_textured_line(t_data *data, t_wall *wall, t_ray *ray, int x)
{
	mlx_texture_t	*texture;
	double			wall_x;
	int				tex_x;

	wall->x = x;
	texture = select_wall_texture(data, ray);
	wall_x = get_wall_x(data, ray);
	tex_x = get_tex_x(ray, wall_x, texture);
	draw_vertical_line(data, wall, texture, tex_x);
}
