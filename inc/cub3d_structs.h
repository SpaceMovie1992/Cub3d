/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:09:48 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/03 22:10:31 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 800
# define FOV 60
# define TILE_SIZE 64
# define SPEED 5
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4
# define NORTH 4.7123889804
# define SOUTH 1.5707963268
# define WEST 3.1415926535
# define EAST 0

typedef struct s_player
{
	double	player_x;
	double	player_y;
	double	angle;
	float	fov;
	int		rotation;
	int		l_r;
	int		u_d;
}	t_player;

typedef struct s_ray
{
	double	angle;
	double	distance;
	int		wall_hit;
	double	hit_x;
	double	hit_y;
}	t_ray;

typedef struct s_texture
{
	mlx_texture_t	*img;
	int			width;
	int			height;
	char		*path;
	mlx_texture_t *texture;
}	t_texture;
typedef struct s_data
{
	mlx_image_t		*img;
	char			**map;
	t_texture		*no_texture;
	t_texture		*so_texture;
	t_texture		*we_texture;
	t_texture		*ea_texture;
	char			*path;
	char			player_dir;
	int				fd;
	int				height;
	int				width;
	int				floor_color;
	int				ceiling_color;
	int				pos_x;
	int				pos_y;
	void			*mlx;
	t_player		player;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}	t_data;

typedef struct s_draw_params {
    t_data      *data;
    mlx_image_t *img;
} t_draw_params;

#endif
