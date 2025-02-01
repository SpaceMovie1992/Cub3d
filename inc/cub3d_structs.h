/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:09:48 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/01 17:59:33 by mstefano         ###   ########.fr       */
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
# define NORTH 4.7123889804 // 3 * PI / 2
# define SOUTH 1.5707963268 // PI / 2
# define WEST 3.1415926535 // PI
# define EAST 0

typedef struct s_player
{
	int		player_x;
	int		player_y;
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

typedef struct s_data
{
	mlx_image_t	*img;
	char		**map;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	char		*path;
	char		player_dir;
	int			fd;
	int			height;
	int			width;
	int			floor_color;
	int			ceiling_color;
	int			pos_x;
	int			pos_y;
	mlx_t		*mlx;
	t_player	player;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}	t_data;

typedef struct s_draw_params {
    t_data      *data;
    mlx_image_t *img;
} t_draw_params;
#endif
