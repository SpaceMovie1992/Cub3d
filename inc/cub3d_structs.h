/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:09:48 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/03 20:19:25 by mstefano         ###   ########.fr       */
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
# define MINIMAP_SCALE 0.2
# define MINIMAP_TILE_SIZE 10
# define MINIMAP_PADDING 20
# define MINIMAP_PLAYER_SIZE 4
# define MINIMAP_WALL_COLOR 0xFFFFFFFF
# define MINIMAP_FLOOR_COLOR 0x444444FF
# define MINIMAP_PLAYER_COLOR 0xFF0000FF
# define MINIMAP_BORDER_COLOR 0x888888FF

typedef struct s_player
{
	double	player_x;
	double	player_y;
	double	angle;
	float	fov;
	int		rotation;
	int		l_r;
	int		u_d;
	double	prev_x;
	double	prev_y;
}	t_player;

typedef struct s_ray
{
	double	angle;
	double	distance;
	int		wall_hit;
	double	hit_x;
	double	hit_y;
}	t_ray;

typedef struct s_minimap
{
	int			size;
	int			pos_x;
	int			pos_y;
	int			width;
	int			height;
	mlx_image_t	*img;
	bool	is_visible;
}   t_minimap;

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
	void		*win;
	t_minimap	minimap;
}	t_data;

typedef struct s_draw_params {
    t_data      *data;
    mlx_image_t *img;
} t_draw_params;


#endif
