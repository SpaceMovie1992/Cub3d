/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:23:29 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/03 21:57:05 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void load_textures(t_data *data)
{
    data->no_texture->img = mlx_load_png("textures/north.png");
    data->so_texture->img = mlx_load_png("textures/south.png");
    data->we_texture->img = mlx_load_png("textures/west.png");
    data->ea_texture->img = mlx_load_png("textures/east.png");

    if (!data->no_texture->img || !data->so_texture->img ||
        !data->we_texture->img || !data->ea_texture->img)
    {
        printf("Error: Failed to load textures\n");
        exit(1);
    }
}


uint32_t get_texture_pixel(t_texture *texture, int x, int y)
{
    uint32_t *pixels = (uint32_t *)texture->img->pixels;
    return pixels[y * texture->img->width + x];
}
